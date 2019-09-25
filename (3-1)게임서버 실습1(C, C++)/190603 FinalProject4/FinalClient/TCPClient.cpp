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
Logs playerLog("나", 5, 0, 0);
Logs enemyLog("적", 5, 70, 0);


// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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

// 사용자 정의 데이터 수신 함수
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

// 로그인 시도
// true 반환시 루프, false 반환시 진행
bool loginToServer(SOCKET& sock, LoginPack* pack, SOCKADDR_IN& addr)
{
	SOCKET tempSock = sock;

	char temp[512];

	int retval;

	// 1. 내 정보가 담긴 패킷을 로그인 서버에 보낸다.
	retval = send(tempSock, (char*)pack, sizeof(LoginPack), 0);

	// 2. 그에 답장이 온 패킷을 확인하고 패킷에 따라 행동한다.
	retval = recvn(tempSock, temp, sizeof(LoginConfirm), 0);
	temp[sizeof(LoginConfirm) - 1] = '\0';
	LoginConfirm* tempCon;
	tempCon = (LoginConfirm*)temp;
	
	// 3. 로그인 성공 시 게임서버와 연결한다.
	if (tempCon->isLogin == true)
	{
		// 연결 해지 X -> closesocket은 소켓 제거 였음
		closesocket(sock);
		// 연결 해지? -> 이것도 안됨, 스트림을 종료하는 함수지만 재연결이 불가
		//shutdown(sock, SD_BOTH);
		// 재연결
		addr = tempCon->serverAddr;
		//retval = connect(udpSock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
		//if (retval == -1)
		//{
		//	printf("실패");
		//}
		//printf("성공");

		return false;
	}
	// 3. 로그인 실패 시 재시도 한다.
	else
	{
		return true;
	}
}

DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;

	int retval;

	// 데이터 통신에 사용할 변수
	char buf[BUFSIZE + 1];
	int len;

	// 데이터 통신에 사용할 변수
	SOCKADDR_IN peeraddr;
	int addrlen;

	// 게임에 사용하는 변수


	while (1)
	{
		// 데이터 받기
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

		// 받은 데이터 출력
		buf[retval] = '\0';
		/*printf("[UDP/%s:%d] %s\n", inet_ntoa(peeraddr.sin_addr),
			ntohs(peeraddr.sin_port), buf);*/
	}

	// closesocket()
	closesocket(sock);
	printf("클라이언트 종료");

	return 0;
}

int main(int argc, char *argv[])
{
	int retval;

	srand(time(NULL));

	// 윈속 초기화
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

	// 데이터 통신에 사용할 변수
	char buf[BUFSIZE+1];
	int len;

	// 회원가입과 로그인 선택
	int login = 0;
	bool isLogin = false;
	printf("1. 회원가입\n2. 로그인\n");
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
		printf("ID를 입력해주세요.(20자 이내)");
		scanf("%s", newId);
		printf("PassWord를 입력해주세요.(20자 이내)");
		scanf("%s", newPass);

		send(sock, newId, sizeof(newId), 0);
		send(sock, newPass, sizeof(newPass), 0);

		recvn(sock, &loginBuf, sizeof(char), 0);

		isLogin = loginBuf;
		if (!isLogin)
			exit(0);
	}
	// 로그인 패킷 만들기
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
	// 확인
	printf("LoginToServer 실행 완료 / 로그인 성공\n\n");

	getchar();

	// 여기까지가 로그인 서버에서 로그인 확인 > 게임 서버 주소를 받아옴
	// 이후는 게임 서버

	SOCKET udpSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSock == INVALID_SOCKET) err_quit("socket()");

	// 브로드캐스팅 활성화
	BOOL bEnable = TRUE;
	retval = setsockopt(udpSock, SOL_SOCKET, SO_BROADCAST,
		(char *)&bEnable, sizeof(bEnable));
	if (retval == SOCKET_ERROR) err_quit("setsockopt()");

	// 소켓 주소 구조체 초기화
	SOCKADDR_IN remoteaddr;
	ZeroMemory(&remoteaddr, sizeof(remoteaddr));
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_addr.s_addr = inet_addr(REMOTEIP);
	remoteaddr.sin_port = htons(9100);

	HANDLE hThread;
	// 스레드 생성 받기만 하는 스레드
	hThread = CreateThread(NULL, 0, ProcessClient,
		(LPVOID)udpSock, 0, NULL);
	if (hThread == NULL) { closesocket(udpSock); }
	else { CloseHandle(hThread); }

	LoginAccept accept;
	accept.check = 2;
	strcpy(accept.name, "없음");
	accept.nameLength = 0;
	accept.userAddr = remoteaddr;


	// 데이터 보내기
	retval = sendto(udpSock, (char*)&accept, sizeof(LoginAccept), 0,
		(SOCKADDR *)&remoteaddr, sizeof(remoteaddr));
	if (retval == SOCKET_ERROR) {
		err_display("sendto()");
		//continue;
	}
	printf("[UDP] %d바이트를 보냈습니다.\n", retval);

	system("cls");

	// 게임 클라이언트 준비
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
		
		// 데이터 보내기
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


	// 게임 서버와 데이터 통신
	//while (1)
	//{
	//	// 데이터 입력
	//	printf("\n[보낼 데이터] ");
	//	if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
	//		break;

	//	// '\n' 문자 제거
	//	len = strlen(buf);
	//	if (buf[len - 1] == '\n')
	//		buf[len - 1] = '\0';
	//	if (strlen(buf) == 0)
	//		break;

	//	// 데이터 보내기
	//	retval = sendto(udpSock, buf, strlen(buf), 0,
	//		(SOCKADDR *)&remoteaddr, sizeof(remoteaddr));
	//	if (retval == SOCKET_ERROR) {
	//		err_display("sendto()");
	//		continue;
	//	}
	//	// printf("[UDP] %d바이트를 보냈습니다.\n", retval);
	//}

	// closesocket()
	closesocket(udpSock);

	// 윈속 종료
	WSACleanup();
	return 0;
}