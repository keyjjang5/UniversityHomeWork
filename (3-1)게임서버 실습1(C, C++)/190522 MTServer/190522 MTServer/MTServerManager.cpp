// #include "stdafx.h"
#include "MTServerManager.h"
#include "ClientSession.h"
#include "SessionManager.h"

using namespace std;

MTServerManager* GMTServerManager = nullptr;
MTServerManager::MTServerManager() : mListenSocket(NULL){}
MTServerManager::~MTServerManager(){}

//서버를 초기화해줄 함수입니다. 기본적인 내용이니 다음으로 넘어가겠습니다.

bool MTServerManager::InitServer()
{
	WSADATA wsaData;
	int iResult;
	SOCKADDR_IN serveraddr;
	//서버 주소 초기화.
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//서버 시작.
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//2.2 
	if (iResult){
		cout << "WSA startup failed" <<endl;
		return false;
	}
	//서버 소켓 생성.
	mListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mListenSocket == INVALID_SOCKET){
		cout << "Invalid socket" << endl;		
		return false;
	}
	//서버 소켓 주소와 연결.
	iResult = bind(mListenSocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (iResult){
		cout << "bind failed : " << GetLastError() << endl;
		return false;
	}
	//응답대기 시작.
	iResult = listen(mListenSocket, SOMAXCONN);
	if (iResult){
		cout << "listen failed : " << GetLastError() << endl;
		return false;
	}
	return true;
}
void MTServerManager::CloseServer()
{
	//소켓 종료
	closesocket(mListenSocket);
	//윈속 종료
	WSACleanup();
}

//CAcceptLoop()함수는 클라이언트의 접속과 스레드의 생성을 담당하는 함수입니다. CreateThread()함수를 이용해 작업자 스레드를 생성해주고 있습니다. 

bool MTServerManager::CAcceptLoop()
{
	HANDLE hThread;
	while (true){
		//접속 소켓 생성.
		SOCKET acceptSock = accept(mListenSocket, NULL, NULL);
		if (acceptSock == INVALID_SOCKET){
			cout << "accept error : Invalid socket..." << endl;
			continue;
		}
		SOCKADDR_IN clientAddr;
		int AddrLen = sizeof(clientAddr);
		getpeername(acceptSock, (SOCKADDR*)&clientAddr, &AddrLen);
		
		//클라이언트 생성.
		ClientSession * client = GSessionManager->CreateClient(acceptSock);

		//클라접속처리.
		if (client->OnConnect(&clientAddr) == false)
		{
			cout << "connect error..." <<endl;
			client->Disconnect();
			GSessionManager->DeleteClient(client);
		}
		// thread 생성 후 클라이언트 넘기기.
		hThread = CreateThread(NULL, 0 ,WorkerThread, (LPVOID)client,0, NULL);
		if (hThread == NULL)
		{
			cout << "Create thread error..." <<endl;
			client->Disconnect();
			GSessionManager->DeleteClient(client);
		}
		else
		{
			CloseHandle(hThread);
		}
	}
}

//작업자 스레드로 사용할 스레드 함수입니다. ClientSession의 송수신 함수로 작동되며 Echo기능만 합니다.

DWORD WINAPI MTServerManager::WorkerThread(LPVOID lpParam)
{
	//전달된 클라이언트를 저장.
	ClientSession * client = (ClientSession*)lpParam;

	while (true){
		//수신 실패시
		if (client->Recv() == false){
			//클라 삭제.
			GSessionManager->DeleteClient(client);
			return 1;
		}
		//송신 실패시
		if (client->Send() == false){
			//클라 삭제.
			GSessionManager->DeleteClient(client);
			return 1;
		}
	}	return 0;
}
