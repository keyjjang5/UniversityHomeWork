#pragma once
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000
#define BUFSIZE    512


class TCPServer
{
private:
	int retval;
	WSADATA wsa;
	SOCKET listen_sock;
	SOCKADDR_IN serveraddr;

	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;

	int share;

public:
	CRITICAL_SECTION cs;
	DWORD (*funtion)(LPVOID arg);

public:
	TCPServer();
	int Initialize();
	void End();
	void Socket();
	void Bind();
	void Listen();
	void Accept();
	void MCreateThread(LPTHREAD_START_ROUTINE processClient);

	void Print();

	void err_quit(char *msg);
	void err_display(char *msg);
	DWORD WINAPI ProcessClient(LPVOID arg);

	void SwitchShare(SOCKET client_sock);
	void ChangeShare(int i);

};

TCPServer::TCPServer()
{

}

int  TCPServer::Initialize()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	EnterCriticalSection(&cs);

}

void TCPServer::End()
{
	DeleteCriticalSection(&cs);

	// closesocket()
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
}

void TCPServer::Socket()
{
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");
}

void TCPServer::Bind()
{
	serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");
}

void TCPServer::Listen()
{
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");
}

void TCPServer::Accept()
{
	addrlen = sizeof(clientaddr);
	client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
	if (client_sock == INVALID_SOCKET) {
		err_display("accept()");
		return;
	}
}

void TCPServer::MCreateThread(LPTHREAD_START_ROUTINE processClient)
{
	hThread = CreateThread(NULL, 0, processClient,
		(LPVOID)client_sock, 0, NULL);
	if (hThread == NULL) { closesocket(client_sock); }
	else { CloseHandle(hThread); }
}

void TCPServer::Print()
{
	printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
}

void TCPServer::err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void TCPServer::err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

DWORD WINAPI TCPServer::ProcessClient(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR *)&clientaddr, &addrlen);

	//SwitchShare(client_sock);


	while (1) {
		// 데이터 받기
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// 받은 데이터 출력
		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), buf);

		// 데이터 보내기
		retval = send(client_sock, buf, retval, 0);
		if (retval == SOCKET_ERROR) {
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

void TCPServer::SwitchShare(SOCKET client_sock)
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

void TCPServer::ChangeShare(int i)
{
	EnterCriticalSection(&cs);
	share += i;
	LeaveCriticalSection(&cs);
	printf("Share Value : %d", share);
}