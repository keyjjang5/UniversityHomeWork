#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#include "PacketCollection.h"

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    512

#define REMOTEIP   "255.255.255.255"
#define REMOTEPORT 9100


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
bool loginToServer(SOCKET& sock, LoginPack* pack, SOCKADDR_IN& addr)
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
		addr = tempCon->serverAddr;
		//retval = connect(udpSock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
		//if (retval == -1)
		//{
		//	printf("����");
		//}
		//printf("����");

		return false;
	}
	// 3. �α��� ���� �� ��õ� �Ѵ�.
	else
	{
		return true;
	}
}

DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;

	int retval;

	// ������ ��ſ� ����� ����
	char buf[BUFSIZE + 1];
	int len;

	// ������ ��ſ� ����� ����
	SOCKADDR_IN peeraddr;
	int addrlen;
	while (1)
	{
		// ������ �ޱ�
		addrlen = sizeof(peeraddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0,
			(SOCKADDR *)&peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom()");
			continue;
		}

		// ���� ������ ���
		buf[retval] = '\0';
		printf("[UDP/%s:%d] %s\n", inet_ntoa(peeraddr.sin_addr),
			ntohs(peeraddr.sin_port), buf);
	}

	// closesocket()
	closesocket(sock);
	printf("Ŭ���̾�Ʈ ����");

	return 0;
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
		isLoop = loginToServer(sock, &loginPack, serveraddr);
	} while (isLoop == true);
	// Ȯ��
	printf("LoginToServer ���� �Ϸ� / �α��� ����");

	getchar();

	// ��������� �α��� �������� �α��� Ȯ�� > ���� ���� �ּҸ� �޾ƿ�
	// ���Ĵ� ���� ����

	SOCKET udpSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSock == INVALID_SOCKET) err_quit("socket()");

	// ��ε�ĳ���� Ȱ��ȭ
	BOOL bEnable = TRUE;
	retval = setsockopt(udpSock, SOL_SOCKET, SO_BROADCAST,
		(char *)&bEnable, sizeof(bEnable));
	if (retval == SOCKET_ERROR) err_quit("setsockopt()");

	// ���� �ּ� ����ü �ʱ�ȭ
	SOCKADDR_IN remoteaddr;
	ZeroMemory(&remoteaddr, sizeof(remoteaddr));
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_addr.s_addr = inet_addr(REMOTEIP);
	remoteaddr.sin_port = htons(9100);

	HANDLE hThread;
	// ������ ���� �ޱ⸸ �ϴ� ������
	hThread = CreateThread(NULL, 0, ProcessClient,
		(LPVOID)udpSock, 0, NULL);
	if (hThread == NULL) { closesocket(udpSock); }
	else { CloseHandle(hThread); }

	LoginAccept accept;
	accept.check = 2;
	strcpy(accept.name, "����");
	accept.nameLength = 0;
	accept.userAddr = remoteaddr;


	// ������ ������
	retval = sendto(udpSock, (char*)&accept, sizeof(LoginAccept), 0,
		(SOCKADDR *)&remoteaddr, sizeof(remoteaddr));
	if (retval == SOCKET_ERROR) {
		err_display("sendto()");
		//continue;
	}
	printf("[UDP] %d����Ʈ�� ���½��ϴ�.\n", retval);

	// ���� ������ ������ ���
	while (1)
	{
		// ������ �Է�
		printf("\n[���� ������] ");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' ���� ����
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// ������ ������
		retval = sendto(udpSock, buf, strlen(buf), 0,
			(SOCKADDR *)&remoteaddr, sizeof(remoteaddr));
		if (retval == SOCKET_ERROR) {
			err_display("sendto()");
			continue;
		}
		printf("[UDP] %d����Ʈ�� ���½��ϴ�.\n", retval);
	}

	// closesocket()
	closesocket(udpSock);

	// ���� ����
	WSACleanup();
	return 0;
}