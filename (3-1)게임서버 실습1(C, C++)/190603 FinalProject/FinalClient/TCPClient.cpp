#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#include "PacketCollection.h"

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    512


SOCKET mSock;


// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCTSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while(left > 0){
		received = recv(s, ptr, left, flags);
		if(received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if(received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

// ����
void SwitchShare(SOCKET sock)
{
	int temp;

	int retval;

	retval = recvn(sock, (char*)&temp, sizeof(int), 0);

	printf("\ntemp : %d", temp);

	temp += 10;

	retval = send(sock, (char*)&temp, sizeof(int), 0);
}

// �α��� �õ�
// true ��ȯ�� ����, false ��ȯ�� ����
bool loginToServer(SOCKET& sock, LoginPack* pack)
{
	SOCKET tempSock = sock;

	char temp[512];

	int retval;

	// 1. �� ������ ��� ��Ŷ�� �α��� ������ ������.
	retval = send(tempSock, (char*)pack, sizeof(LoginPack), 0);

	// 2. �׿� ������ �� ��Ŷ�� Ȯ���ϰ� ��Ŷ�� ���� �ൿ�Ѵ�.
	retval = recvn(tempSock, temp, sizeof(LoginConfirm), 0);
	temp[sizeof(LoginConfirm) - 1] = '\0';
	LoginConfirm* tempCon;
	tempCon = (LoginConfirm*)temp;
	
	// 3. �α��� ���� �� ���Ӽ����� �����Ѵ�.
	if (tempCon->isLogin == true)
	{
		// ���� ���� X -> closesocket�� ���� ���� ����
		closesocket(sock);
		// ���� ����? -> �̰͵� �ȵ�, ��Ʈ���� �����ϴ� �Լ����� �翬���� �Ұ�
		//shutdown(sock, SD_BOTH);
		// �翬��
		SOCKADDR_IN serveraddr;
		serveraddr = tempCon->serverAddr;
		retval = connect(mSock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
		if (retval == -1)
		{
			printf("����");
		}
		printf("����");

		return false;
	}
	// 3. �α��� ���� �� ��õ� �Ѵ�.
	else
	{
		return true;
	}
}

int main(int argc, char *argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET) err_quit("socket()");

	mSock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("connect()");

	// ������ ��ſ� ����� ����
	char buf[BUFSIZE+1];
	int len;

	// ����
	// SwitchShare(sock);

	// �α��� ��Ŷ �����
	LoginPack loginPack;

	printf("Id : ");
	scanf("%s", loginPack.uId);
	printf("PassWord : ");
	scanf("%s", loginPack.uPw);

	loginPack.idLength = strlen(loginPack.uId);
	loginPack.pwLength = strlen(loginPack.uPw);

	bool isLoop = false;
	do
	{
		isLoop = loginToServer(sock, &loginPack);
	} while (isLoop == true);
	// Ȯ��
	printf("LoginToServer ���� �Ϸ� / �α��� ����");
	// ���Ĵ� ���� ����

	getchar();

	// ������ ������ ���
	while(1)
	{
		// ������ �Է�
		printf("\n[���� ������] ");
		if(fgets(buf, BUFSIZE+1, stdin) == NULL)
			break;
	
		printf("check\n");

		// '\n' ���� ����
		len = strlen(buf);
		if(buf[len-1] == '\n')
			buf[len-1] = '\0';
		if(strlen(buf) == 0)
			break;

		printf("check\n");

		// ������ ������
		retval = send(mSock, buf, strlen(buf), 0);
		if(retval == SOCKET_ERROR){
			err_display("send()");
			break;
		}
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);

		// ������ �ޱ�
		retval = recvn(mSock, buf, retval, 0);
		if(retval == SOCKET_ERROR){
			err_display("recv()");
			break;
		}
		else if(retval == 0)
			break;

		// ���� ������ ���
		buf[retval] = '\0';
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� �޾ҽ��ϴ�.\n", retval);
		printf("[���� ������] %s\n", buf);
	}

	// closesocket()
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;
}