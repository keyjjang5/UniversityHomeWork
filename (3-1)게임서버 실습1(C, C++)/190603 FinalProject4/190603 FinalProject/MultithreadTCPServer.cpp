#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "PacketCollection.h"

using namespace std;

#define SERVERPORT 9000
#define GAMESERVERPORT 9100
#define BUFSIZE    512

// 과제
CRITICAL_SECTION cs;
int share = 0;

// 로그인 데이터(추후 파일로 변경)
char serverUid[20] = "nickname";
char serverUpass[20] = "server";
string userId[10];
string userPass[10];

int number = 0;

void ReadData();

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
	bool isData = false;

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
	for (int i = 0; i < number; i++)
	{
		if (strcmp(uid, userId[i].c_str()) == 0 && strcmp(upass, userPass[i].c_str()) == 0)
		{
			isData = true;
			break;
		}
	}
	if (isData)
	{
		SOCKADDR_IN serveraddr;
		ZeroMemory(&serveraddr, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = inet_addr("255.255.255.255");
		serveraddr.sin_port = htons(GAMESERVERPORT);

		LoginConfirm* confirm = new LoginConfirm;
		confirm->isLogin = true;
		confirm->serverAddr = serveraddr;

		retval = send(sock, (char*)confirm, sizeof(LoginConfirm), 0);

		//// UDP 소켓을 만들고 그것을 통해 게임 서버에게 정보 전달
		//// socket()
		//SOCKET udpSock = socket(AF_INET, SOCK_DGRAM, 0);
		//if (udpSock == INVALID_SOCKET) err_quit("socket()");

		//// 브로드캐스팅 활성화
		//BOOL bEnable = TRUE;
		//retval = setsockopt(udpSock, SOL_SOCKET, SO_BROADCAST,
		//	(char *)&bEnable, sizeof(bEnable));
		//if (retval == SOCKET_ERROR) err_quit("setsockopt()");

		//// 소켓 주소 구조체 초기화
		//SOCKADDR_IN remoteaddr;
		//ZeroMemory(&remoteaddr, sizeof(remoteaddr));
		//remoteaddr.sin_family = AF_INET;
		//remoteaddr.sin_addr.s_addr = inet_addr("255.255.255.255"); // 브로드 캐스트 주소
		//remoteaddr.sin_port = htons(GAMESERVERPORT);

		//// 데이터 보내기
		//retval = sendto(sock, (char*)sock, sizeof(SOCKET), 0,
		//	(SOCKADDR *)&remoteaddr, sizeof(remoteaddr));
		//if (retval == SOCKET_ERROR) {
		//	err_display("sendto()");
		//}
		
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
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR *)&clientaddr, &addrlen);

	// 회원가입 or 로그인 판정
	retval = recv(client_sock, buf, sizeof(char), 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}
	bool isJoin;
	isJoin = (bool)buf[0];
	if (!isJoin)
	{
		FILE *fp;

		fp = fopen("UserData.txt", "a");

		// ID 받기
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
		}

		buf[retval+1] = '\0';
		printf("신규 생성 ID : %s\n", buf);
		fprintf(fp, buf);
		fprintf(fp, " ");

		// PassWord 받기
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
		}

		buf[retval] = '\0';
		printf("신규 생성 PassWord : %s\n", buf);
		fprintf(fp, buf);
		fprintf(fp, "\n");

		fclose(fp);

		// 회원가입 성공 메시지 보내기
		isJoin = true;
		buf[0] = isJoin;
		send(client_sock, buf, sizeof(char), 0);

		number = 0;
		ReadData();
	}
	
	// 로그인 확인
	bool isLoop = false;
	do
	{
		isLoop = LoginFromClient(client_sock);
	} while (isLoop == true);
	// 확인
	printf("LoginFromClient 실행 완료");

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

	// 파일 입출력에 사용하는 변수
	FILE *fp;
	fp = fopen("Log.txt", "a");

	time_t now;
	time(&now);
	tm* nowLocal = localtime(&now);

	// 파일 입력
	fprintf(fp, "%d년 %d월 %d일 %d시 %d분 %d초 : ",
		nowLocal->tm_year + 1900,
		nowLocal->tm_mon + 1,
		nowLocal->tm_mday,
		nowLocal->tm_hour,
		nowLocal->tm_min,
		nowLocal->tm_sec);

	fprintf(fp, "[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	fclose(fp);

	return 0;
}

void ReadData()
{
	bool done = false;
	ifstream fin;
	char input;
	char filename[20] = "UserData.txt";

	int count = 0;
	


	// 로그인 확인용 데이터
	char tempId[20];
	char tempPass[20];


	fin.open(filename);
	if (fin.good())
	{
		done = true;
	}
	else
	{
		// If the file does not exist or there was an issue opening it then notify the user and repeat the process.
		fin.clear();
		cout << endl;
		cout << "File " << filename << " could not be opened." << endl << endl;
	}

	fin.close();

	fin.open(filename);
	if (fin.fail() == true)
	{
		return;
	}

	fin.get(input);
	while (!fin.eof())
	{
		tempId[count] = input;
		while (1)
		{
			fin.get(input);
			if (input == ' ')
			{
				++count;
				tempId[count] = '\0';
				break;
			}
			++count;

			tempId[count] = input;
		}
		count = 0;

		// 파일에서 유저 패스워드 뽑아내기
		fin.get(input);
		tempPass[count] = input;
		while (1)
		{
			fin.get(input);
			if (input == '\n')
			{
				++count;

				tempPass[count] = '\0';
				break;
			}
			++count;

			tempPass[count] = input;
		}
		count = 0;
		if (input == '\n')
		{
			userId[number].clear();
			userId[number].append(tempId);
			userPass[number].clear();
			userPass[number].append(tempPass);

			cout << "userId : " << userId[number] << endl;
			cout << "userPass : " << userPass[number] << endl;

			++number;
		}

		fin.get(input);
	}
}

int main(int argc, char *argv[])
{
	// criticalSection
	InitializeCriticalSection(&cs);

	// 파일 입출력에 사용하는 변수
	FILE *fp;

	time_t now;
	time(&now);
	tm* nowLocal = localtime(&now);

	// 로그인 확인용 데이터
	ReadData();


	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if(retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;

	while(1){
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if(client_sock == INVALID_SOCKET){
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		
		// 파일 입력
		fp = fopen("Log.txt", "a");
		
		fprintf(fp, "%d년 %d월 %d일 %d시 %d분 %d초 : ",
			nowLocal->tm_year + 1900,
			nowLocal->tm_mon + 1,
			nowLocal->tm_mday,
			nowLocal->tm_hour,
			nowLocal->tm_min,
			nowLocal->tm_sec);
		fprintf(fp, "[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		fclose(fp);
		
		// 회원가입 or 로그인 판정
		

		// 스레드 생성
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);
		if(hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}

	DeleteCriticalSection(&cs);

	// closesocket()
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}