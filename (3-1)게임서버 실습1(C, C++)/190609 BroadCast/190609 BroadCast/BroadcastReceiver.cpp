#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

#define LOCALPORT 9000
#define BUFSIZE   512


// 로그인 서버 -> 게임 서버 로 보내는 로그인 확인 + 인계 패킷
typedef struct loginAccept
{
	int check;
	// User Ip
	// User Port
	SOCKADDR_IN userAddr;

	// User Name Length
	int nameLength;
	// User Name
	char name[20];

	// User Level... etc
}LoginAccept;

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

int main(int argc, char *argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN localaddr;
	ZeroMemory(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(LOCALPORT);
	retval = bind(sock, (SOCKADDR *)&localaddr, sizeof(localaddr));
	if(retval == SOCKET_ERROR) err_quit("bind()");

	// 브로드캐스팅 활성화
	BOOL bEnable = TRUE;
	retval = setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
		(char *)&bEnable, sizeof(bEnable));
	if (retval == SOCKET_ERROR) err_quit("setsockopt()");

	// 데이터 통신에 사용할 변수
	SOCKADDR_IN peeraddr;
	int addrlen;
	char buf[BUFSIZE+1];

	SOCKADDR_IN connectedAddr[10];
	int i = 0;

	// 브로드캐스트 데이터 받기
	while(1){
		// 데이터 받기
		addrlen = sizeof(peeraddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0,
			(SOCKADDR *)&peeraddr, &addrlen);
		if(retval == SOCKET_ERROR){
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

			continue;
		}


		// 받은 데이터 출력
		buf[retval] = '\0';
		printf("[UDP/%s:%d] %s\n", inet_ntoa(peeraddr.sin_addr),
			ntohs(peeraddr.sin_port), buf);


		// 데이터 보내기
		for (int j = 0; j <= i-1; j++)
		{
			retval = sendto(sock, buf, strlen(buf), 0,
				(SOCKADDR *)&connectedAddr[j], sizeof(connectedAddr[j]));
			if (retval == SOCKET_ERROR) {
				err_display("sendto()");
				continue;
			}

			printf("[UDP] %d바이트를 보냈습니다.\n", retval);
			printf("ip : %s, port : %d에 보냈습니다.\n",
				inet_ntoa(connectedAddr[j].sin_addr),
				ntohs(connectedAddr[j].sin_port));
		}
		
	}

	// closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}