#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#include "PacketCollection.h"

#define SERVERPORT 9100
#define BUFSIZE    512

// ����
CRITICAL_SECTION cs;
int share = 0;

// �α��� ������(���� ���Ϸ� ����)
char serverUid[20] = "nickname";
char serverUpass[20] = "server";

bool action[10] = { false };

void ChangeShare(int i)
{
	EnterCriticalSection(&cs);
	share += i;
	LeaveCriticalSection(&cs);
	printf("Share Value : %d", share);
}

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
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

// ����
void SwitchShare(SOCKET client_sock)
{
	// ���� �߰��� : share �� �۽�
	int temp, temp2;

	int retval;
	char buf[BUFSIZE + 1];

	itoa(share, buf, 10);

	temp = share;

	retval = send(client_sock, (char*)&temp, sizeof(int), 0);


	retval = recv(client_sock, (char*)&temp2, sizeof(int), 0);
	printf("\ntemp : %d", temp2);
	temp2 -= temp;
	ChangeShare(temp2);
	printf("üũ");

	printf("changeShare");
}

// �α��� ����
bool LoginFromClient(SOCKET& client_sock)
{
	SOCKET sock = client_sock;
	int retval;
	char temp[sizeof(LoginPack)];
	bool isLoop = false;

	// 1. Ŭ���̾�Ʈ�� ���� ��Ŷ�� �޴´�.
	retval = recv(sock, (char*)temp, sizeof(LoginPack), 0);
	temp[sizeof(LoginPack) - 1] = '\0';
	// 2. ��Ŷ�� �����Ϳ� ���Ѵ�.
	LoginPack* tempPack;
	tempPack = (LoginPack*)temp;
	char uid[20];
	strcpy(uid, tempPack->uId);
	char upass[20];
	strcpy(upass, tempPack->uPw);
	
	// 3. �ùٸ� �α��� ������ �޾Ҵٸ� ���θ޽����� ������.
	if (strcmp(uid, serverUid) == 0 && strcmp(upass, serverUpass) == 0)
	{
		SOCKADDR_IN serveraddr;
		ZeroMemory(&serveraddr, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
		serveraddr.sin_port = htons(SERVERPORT);

		LoginConfirm* confirm = new LoginConfirm;
		confirm->isLogin = true;
		confirm->serverAddr = serveraddr;

		retval = send(sock, (char*)confirm, sizeof(LoginConfirm), 0);

		
		// 4. ���ÿ� ���Ӽ����� �÷��̾� ������ �Ѱ��ش�.
		// �α��� - Ŭ���̾�Ʈ ���� Ȯ���ϰ� �߰�

		delete confirm;

		isLoop = false;
	}
	// 3. Ʋ�� �α��� ������ �޾Ҵٸ� �źθ޽����� ������.
	else
	{
		LoginConfirm* confirm = new LoginConfirm;
		confirm->isLogin = false;

		retval = send(sock, (char*)confirm, sizeof(LoginConfirm), 0);

		delete confirm;

		isLoop = true;
	}


	return isLoop;
}

// Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI ProcessClient(LPVOID arg)
{
	ThreadNum* tNum = (ThreadNum*)arg;
	SOCKET client_sock = tNum->sock;
	int num = tNum->num;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR *)&clientaddr, &addrlen);

	printf("my num : %d", num);

	// ����
	//SwitchShare(client_sock);
	
	// �α��� Ȯ��
	//bool isLoop = false;
	//do
	//{
	//	isLoop = LoginFromClient(client_sock);
	//} while (isLoop == true);
	//// Ȯ��
	//printf("LoginFromClient ���� �Ϸ�");

	while(1){

		// ������ �ޱ�
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if(retval == SOCKET_ERROR){
			err_display("recv()");
			break;
		}
		else if(retval == 0)
			break;

		// ���� ������ ���
		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), buf);

		// ������ ������
		retval = send(client_sock, buf, retval, 0);
		if(retval == SOCKET_ERROR){
			err_display("send()");
			break;
		}
	}

	// closesocket()
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}

int main(int argc, char *argv[])
{
	// criticalSection
	InitializeCriticalSection(&cs);

	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return 1;

	//// socket()
	//SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	//if(listen_sock == INVALID_SOCKET) err_quit("socket()");

	//// bind()
	//SOCKADDR_IN serveraddr;
	//ZeroMemory(&serveraddr, sizeof(serveraddr));
	//serveraddr.sin_family = AF_INET;
	//serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//serveraddr.sin_port = htons(SERVERPORT);
	//retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	//if (retval == SOCKET_ERROR) err_quit("bind()");

	//// listen()
	//retval = listen(listen_sock, SOMAXCONN);
	//if (retval == SOCKET_ERROR) err_quit("listen()");

	//// ������ ��ſ� ����� ����
	//SOCKET client_sock;
	//SOCKADDR_IN clientaddr;
	//int addrlen;
	//HANDLE hThread;
	//DWORD threadID;              // ������ ���̵�

	//int i = 0;
	//while (1) {
	//	// accept()
	//	addrlen = sizeof(clientaddr);
	//	client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
	//	if (client_sock == INVALID_SOCKET) {
	//		err_display("accept()");
	//		break;
	//	}

	//	// ������ Ŭ���̾�Ʈ ���� ���
	//	printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
	//		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	//	ThreadNum num;
	//	num.sock = client_sock;
	//	num.num = i;

	//	++i;

	//	// ������ ����
	//	hThread = CreateThread(NULL, 0, ProcessClient,
	//		(LPVOID)&num, 0, &threadID);
	//	if (hThread == NULL) { closesocket(client_sock); }
	//	else { CloseHandle(hThread); }


	//}


	// UdpSocket
	SOCKET udpSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSock == INVALID_SOCKET) err_quit("socket()");

	// udpbind()
	SOCKADDR_IN localaddr;
	ZeroMemory(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(SERVERPORT);
	retval = bind(udpSock, (SOCKADDR *)&localaddr, sizeof(localaddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// ��ε�ĳ���� Ȱ��ȭ
	BOOL bEnable = TRUE;
	retval = setsockopt(udpSock, SOL_SOCKET, SO_BROADCAST,
		(char *)&bEnable, sizeof(bEnable));
	if (retval == SOCKET_ERROR) err_quit("setsockopt()");
	
	// ������ ��ſ� ����� ����
	SOCKADDR_IN peeraddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	SOCKADDR_IN connectedAddr[10];
	int i = 0;

	// ��ε�ĳ��Ʈ ������ �ޱ�
	while (1) {
		// ������ �ޱ�
		addrlen = sizeof(peeraddr);
		retval = recvfrom(udpSock, buf, BUFSIZE, 0,
			(SOCKADDR *)&peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom()");
			continue;
		}

		int check = 0;
		memcpy(&check, buf, sizeof(int));
		printf("check : %d\n", check);

		// login server -> game server packet �̶��
		if (check == 2)
		{
			LoginAccept* accept;
			accept = (LoginAccept*)buf;
			connectedAddr[i] = peeraddr;
			++i;

			continue;
		}


		// ���� ������ ���
		buf[retval] = '\0';
		printf("[UDP/%s:%d] %s\n", inet_ntoa(peeraddr.sin_addr),
			ntohs(peeraddr.sin_port), buf);


		// ������ ������
		for (int j = 0; j <= i - 1; j++)
		{
			retval = sendto(udpSock, buf, strlen(buf), 0,
				(SOCKADDR *)&connectedAddr[j], sizeof(connectedAddr[j]));
			if (retval == SOCKET_ERROR) {
				err_display("sendto()");
				continue;
			}

			printf("[UDP] %d����Ʈ�� ���½��ϴ�.\n", retval);
			printf("ip : %s, port : %d�� ���½��ϴ�.\n",
				inet_ntoa(connectedAddr[j].sin_addr),
				ntohs(connectedAddr[j].sin_port));
		}

	}
	

	

	DeleteCriticalSection(&cs);

	// closesocket()
	closesocket(udpSock);

	// ���� ����
	WSACleanup();
	return 0;
}

