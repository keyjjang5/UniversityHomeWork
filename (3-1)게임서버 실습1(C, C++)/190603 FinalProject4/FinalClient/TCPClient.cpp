#pragma comment(lib, "ws2_32")
#include <stdlib.h>
#include <stdio.h>

#include <WinSock2.h>
#include <Windows.h>

#include "PacketCollection.h"

#include <iostream>
#include <ctime>
#include <conio.h>

#include "Logs.h"

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    512

#define REMOTEIP   "255.255.255.255"
#define REMOTEPORT 9100

int myid;
Logs playerLog("��", 5, 0, 0);
Logs enemyLog("��", 5, 70, 0);


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

	// ���ӿ� ����ϴ� ����


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

		GamePack* temp = (GamePack*)buf;
		
		if (temp->id != myid)
		{
			switch (temp->message)
			{
			case (Message::attack):
				enemyLog.WriteLog(Message::attack);
				break;
			case (Message::doubleAttack):
				enemyLog.WriteLog(Message::doubleAttack);
				break;
			case (Message::defend):
				enemyLog.WriteLog(Message::defend);
				break;
			case (Message::doubleDefend):
				enemyLog.WriteLog(Message::doubleDefend);
				break;
			case (Message::charge):
				enemyLog.WriteLog(Message::charge);
				break;
			}

			enemyLog.SetHp(temp->hp);
			enemyLog.SetEn(temp->en);
		}
		else
		{
			playerLog.SetHp(temp->hp);
			playerLog.SetEn(temp->en);
		}

		// ���� ������ ���
		buf[retval] = '\0';
		/*printf("[UDP/%s:%d] %s\n", inet_ntoa(peeraddr.sin_addr),
			ntohs(peeraddr.sin_port), buf);*/
	}

	// closesocket()
	closesocket(sock);
	printf("Ŭ���̾�Ʈ ����");

	return 0;
}

int main(int argc, char *argv[])
{
	int retval;

	srand(time(NULL));

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET) err_quit("socket()");

	myid = rand();

	printf("my ID : %d\n", myid);

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

	// ȸ�����԰� �α��� ����
	int login = 0;
	bool isLogin = false;
	printf("1. ȸ������\n2. �α���\n");
	scanf("%d", &login);
	switch (login)
	{
	case(1):
		isLogin = false;
		break;
	case(2):
		isLogin = true;
		break;
	}

	char loginBuf;
	loginBuf = (char)isLogin;
	send(sock, &loginBuf, sizeof(char), 0);

	if (!isLogin)
	{
		char newId[20];
		char newPass[20];
		printf("ID�� �Է����ּ���.(20�� �̳�)");
		scanf("%s", newId);
		printf("PassWord�� �Է����ּ���.(20�� �̳�)");
		scanf("%s", newPass);

		send(sock, newId, sizeof(newId), 0);
		send(sock, newPass, sizeof(newPass), 0);

		recvn(sock, &loginBuf, sizeof(char), 0);

		isLogin = loginBuf;
		if (!isLogin)
			exit(0);
	}
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
	printf("LoginToServer ���� �Ϸ� / �α��� ����\n\n");

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

	system("cls");

	// ���� Ŭ���̾�Ʈ �غ�
	Message message;

	GamePack gamePack;

	clock_t current_tick, start_tick;

	bool check = false;

	start_tick = clock();
	while (true)
	{
		current_tick = clock();
		Renderer::getInstance().clear();

		if (_kbhit()) {
			char key = _getch();
			//printf("%d\n", key);
			if (key == 27) break;
			if (key == -32) {
				key = _getch();
			}

			switch (key) {
			case 'q':
				playerLog.WriteLog(Message::attack);
				gamePack.message = Message::attack;
				check = true;
				break;
			case 'w':
				playerLog.WriteLog(Message::doubleAttack);
				gamePack.message = Message::doubleAttack;
				check = true;
				break;
			case 'e':
				playerLog.WriteLog(Message::defend);
				gamePack.message = Message::defend;
				check = true;
				break;
			case 'r':
				playerLog.WriteLog(Message::doubleDefend);
				gamePack.message = Message::doubleDefend;
				check = true;
				break;
			case ' ':
				playerLog.WriteLog(Message::charge);
				gamePack.message = Message::charge;
				check = true;
				break;
			}
		}
		if (main == nullptr) break;

		playerLog.Update();
		enemyLog.Update();
		
		// ������ ������
		if (check == true)
		{
			gamePack.id = myid;
			gamePack.hp = playerLog.GetHp();
			gamePack.en = playerLog.GetEn();

			retval = sendto(udpSock, (char*)&gamePack, sizeof(GamePack), 0,
				(SOCKADDR *)&remoteaddr, sizeof(remoteaddr));
			if (retval == SOCKET_ERROR) {
				err_display("sendto()");
				continue;
			}
		}

		check = false;
		Sleep(50 - (clock() - current_tick));
	}


	// ���� ������ ������ ���
	//while (1)
	//{
	//	// ������ �Է�
	//	printf("\n[���� ������] ");
	//	if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
	//		break;

	//	// '\n' ���� ����
	//	len = strlen(buf);
	//	if (buf[len - 1] == '\n')
	//		buf[len - 1] = '\0';
	//	if (strlen(buf) == 0)
	//		break;

	//	// ������ ������
	//	retval = sendto(udpSock, buf, strlen(buf), 0,
	//		(SOCKADDR *)&remoteaddr, sizeof(remoteaddr));
	//	if (retval == SOCKET_ERROR) {
	//		err_display("sendto()");
	//		continue;
	//	}
	//	// printf("[UDP] %d����Ʈ�� ���½��ϴ�.\n", retval);
	//}

	// closesocket()
	closesocket(udpSock);

	// ���� ����
	WSACleanup();
	return 0;
}