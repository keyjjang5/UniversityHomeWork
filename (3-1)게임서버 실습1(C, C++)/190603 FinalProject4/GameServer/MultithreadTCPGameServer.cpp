#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "PacketCollection.h"

#define SERVERPORT 9100
#define BUFSIZE    512

// 과제
CRITICAL_SECTION cs;
int share = 0;

// 로그인 데이터(추후 파일로 변경)
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

// 소켓 함수 오류 출력 후 종료
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

// 과제
void SwitchShare(SOCKET client_sock)
{
	// 과제 추가분 : share 값 송신
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
	printf("체크");

	printf("changeShare");
}

// 로그인 서버
bool LoginFromClient(SOCKET& client_sock)
{
	SOCKET sock = client_sock;
	int retval;
	char temp[sizeof(LoginPack)];
	bool isLoop = false;

	// 1. 클라이언트가 보낸 패킷을 받는다.
	retval = recv(sock, (char*)temp, sizeof(LoginPack), 0);
	temp[sizeof(LoginPack) - 1] = '\0';
	// 2. 패킷을 데이터와 비교한다.
	LoginPack* tempPack;
	tempPack = (LoginPack*)temp;
	char uid[20];
	strcpy(uid, tempPack->uId);
	char upass[20];
	strcpy(upass, tempPack->uPw);
	
	// 3. 올바른 로그인 정보를 받았다면 승인메시지를 보낸다.
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

		
		// 4. 동시에 게임서버에 플레이어 정보를 넘겨준다.
		// 로그인 - 클라이언트 먼저 확인하고 추가

		delete confirm;

		isLoop = false;
	}
	// 3. 틀린 로그인 정보를 받았다면 거부메시지를 보낸다.
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

// 클라이언트와 데이터 통신
DWORD WINAPI ProcessClient(LPVOID arg)
{
	ThreadNum* tNum = (ThreadNum*)arg;
	SOCKET client_sock = tNum->sock;
	int num = tNum->num;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR *)&clientaddr, &addrlen);

	printf("my num : %d", num);

	// 과제
	//SwitchShare(client_sock);
	
	// 로그인 확인
	//bool isLoop = false;
	//do
	//{
	//	isLoop = LoginFromClient(client_sock);
	//} while (isLoop == true);
	//// 확인
	//printf("LoginFromClient 실행 완료");

	while(1){

		// 데이터 받기
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if(retval == SOCKET_ERROR){
			err_display("recv()");
			break;
		}
		else if(retval == 0)
			break;

		// 받은 데이터 출력
		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), buf);

		// 데이터 보내기
		retval = send(client_sock, buf, retval, 0);
		if(retval == SOCKET_ERROR){
			err_display("send()");
			break;
		}
	}

	// closesocket()
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}

int demageProcess(GamePack* gamePack)
{
	int damage = 0;

	switch (gamePack->message)
	{
	case (Message::attack):
		// 1에게 데미지 1
		damage += 1;
		break;
	case (Message::doubleAttack):
		// 1에게 데미지 2aaaaaaaaaaaaaaa
		damage += 2;
		break;

	default:
		break;
	}

	return damage;
	// 합산해서 각기 데이터 출력 > 보냄 Message사용
}

int defendProcess(GamePack* gamePack, int damage)
{
	switch (gamePack->message)
	{
	case (Message::defend):
		// 받는 데미지 -1(0이하로는 안내려감)
		if (damage > 0)
			damage -= 1;
		break;
	case (Message::doubleDefend):
		// 받는 데미지 -2(0이하로는 안내려감)
		if (damage > 1)
			damage -= 1;
		if (damage > 0)
			damage -= 1;
		break;
	case (Message::charge):
		// 0에게 기력 +1
		// gamePack->en += 1;
		break;

	default:
		break;
	}

	return damage;
}

int main(int argc, char *argv[])
{
	// criticalSection
	InitializeCriticalSection(&cs);

	int retval;

	// 윈속 초기화
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

	//// 데이터 통신에 사용할 변수
	//SOCKET client_sock;
	//SOCKADDR_IN clientaddr;
	//int addrlen;
	//HANDLE hThread;
	//DWORD threadID;              // 스레드 아이디

	//int i = 0;
	//while (1) {
	//	// accept()
	//	addrlen = sizeof(clientaddr);
	//	client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
	//	if (client_sock == INVALID_SOCKET) {
	//		err_display("accept()");
	//		break;
	//	}

	//	// 접속한 클라이언트 정보 출력
	//	printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
	//		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	//	ThreadNum num;
	//	num.sock = client_sock;
	//	num.num = i;

	//	++i;

	//	// 스레드 생성
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

	// 브로드캐스팅 활성화
	BOOL bEnable = TRUE;
	retval = setsockopt(udpSock, SOL_SOCKET, SO_BROADCAST,
		(char *)&bEnable, sizeof(bEnable));
	if (retval == SOCKET_ERROR) err_quit("setsockopt()");
	
	// 데이터 통신에 사용할 변수
	SOCKADDR_IN peeraddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	SOCKADDR_IN connectedAddr[10];
	int i = 0;
	int packCnt = 0;
	GamePack gamePack[2];

	// 파일 입출력 관련 변수
	FILE *fp;

	time_t now;
	time(&now);
	tm* nowLocal = localtime(&now);

	// 브로드캐스트 데이터 받기
	while (1) {
		strcpy(buf, "");
		// 데이터 받기
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

		// login server -> game server packet 이라면
		if (check == 2)
		{
			LoginAccept* accept;
			accept = (LoginAccept*)buf;
			connectedAddr[i] = peeraddr;
			++i;

			// 파일 입력
			fp = fopen("Log.txt", "a");

			fprintf(fp, "%d년 %d월 %d일 %d시 %d분 %d초 : ",
				nowLocal->tm_year + 1900,
				nowLocal->tm_mon + 1,
				nowLocal->tm_mday,
				nowLocal->tm_hour,
				nowLocal->tm_min,
				nowLocal->tm_sec);
			fprintf(fp, "[UDP 게임 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
				inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

			fclose(fp);

			continue;
		}

		if (packCnt != i)
		{
			gamePack[packCnt] = *(GamePack*)buf;

			// 파일 입력
			fp = fopen("Log.txt", "a");

			fprintf(fp, "%d년 %d월 %d일 %d시 %d분 %d초 : ",
				nowLocal->tm_year + 1900,
				nowLocal->tm_mon + 1,
				nowLocal->tm_mday,
				nowLocal->tm_hour,
				nowLocal->tm_min,
				nowLocal->tm_sec);
			fprintf(fp, "[UDP 게임 서버] ID : %d : 클라이언트 접속: 행동 : ",
				gamePack[packCnt].id);

			switch (gamePack[packCnt].message)
			{
			case(Message::attack):
				fprintf(fp, "공격\n");
				break;
			case(Message::doubleAttack):
				fprintf(fp, "이단공격\n");
				break;
			case(Message::defend):
				fprintf(fp, "방어\n");
				break;
			case(Message::doubleDefend):
				fprintf(fp, "이단방어\n");
				break;
			case(Message::charge):
				fprintf(fp, "차징\n");
				break;

			default:
				fprintf(fp, "\n");
				break;
			}

			fclose(fp);

			++packCnt;

			if (packCnt != i)
				continue;
		}

		int damage[2] = { 0 };
		// 0 이 받을 데미지
		damage[0] = demageProcess(&gamePack[1]);
		damage[0] = defendProcess(&gamePack[0], damage[0]);
		// 1 이 받을 데미지
		damage[1] = demageProcess(&gamePack[0]);
		damage[1] = defendProcess(&gamePack[1], damage[1]);

		gamePack[0].hp -= damage[0];
		gamePack[1].hp -= damage[1];
		
		printf("플레이어1의 체력이 %d로 변화", gamePack[0].hp);
		printf("플레이어2의 체력이 %d로 변화", gamePack[1].hp);
		
		// 0에게 1번의 정보를 보냄

		/*retval = sendto(udpSock, (char*)gamePack[1], sizeof(gamePack[1]), 0,
			(SOCKADDR *)&connectedAddr[0], sizeof(connectedAddr[0]));
		if (retval == SOCKET_ERROR) {
			err_display("sendto()");
			continue;
		}*/

		// 받은 데이터 출력
		/*buf[retval] = '\0';
		printf("[UDP/%s:%d] %s\n", inet_ntoa(peeraddr.sin_addr),
			ntohs(peeraddr.sin_port), buf);*/


		// 데이터 보내기
		for (int j = 0; j <= i - 1; j++)
		{
			for (int k = 0; k <= i - 1; k++)
			{
				retval = sendto(udpSock, (char*)&gamePack[j], sizeof(gamePack[j]), 0,
					(SOCKADDR *)&connectedAddr[k], sizeof(connectedAddr[k]));
				if (retval == SOCKET_ERROR) {
					err_display("sendto()");
					continue;
				}

				printf("[UDP] %d바이트를 보냈습니다.\n", retval);
				printf("hp : %d, en : %d, id : %d\n", 
					gamePack[j].hp, gamePack[j].en, gamePack[j].id);
				printf("ip : %s, port : %d에 보냈습니다.\n",
					inet_ntoa(connectedAddr[k].sin_addr),
					ntohs(connectedAddr[k].sin_port));
			}
		}

		packCnt = 0;

	}
	

	

	DeleteCriticalSection(&cs);

	// closesocket()
	closesocket(udpSock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

