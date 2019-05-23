// #include "stdafx.h"
#include "MTServerManager.h"
#include "ClientSession.h"
#include "SessionManager.h"

using namespace std;

MTServerManager* GMTServerManager = nullptr;
MTServerManager::MTServerManager() : mListenSocket(NULL){}
MTServerManager::~MTServerManager(){}

//������ �ʱ�ȭ���� �Լ��Դϴ�. �⺻���� �����̴� �������� �Ѿ�ڽ��ϴ�.

bool MTServerManager::InitServer()
{
	WSADATA wsaData;
	int iResult;
	SOCKADDR_IN serveraddr;
	//���� �ּ� �ʱ�ȭ.
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//���� ����.
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//2.2 
	if (iResult){
		cout << "WSA startup failed" <<endl;
		return false;
	}
	//���� ���� ����.
	mListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mListenSocket == INVALID_SOCKET){
		cout << "Invalid socket" << endl;		
		return false;
	}
	//���� ���� �ּҿ� ����.
	iResult = bind(mListenSocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (iResult){
		cout << "bind failed : " << GetLastError() << endl;
		return false;
	}
	//������ ����.
	iResult = listen(mListenSocket, SOMAXCONN);
	if (iResult){
		cout << "listen failed : " << GetLastError() << endl;
		return false;
	}
	return true;
}
void MTServerManager::CloseServer()
{
	//���� ����
	closesocket(mListenSocket);
	//���� ����
	WSACleanup();
}

//CAcceptLoop()�Լ��� Ŭ���̾�Ʈ�� ���Ӱ� �������� ������ ����ϴ� �Լ��Դϴ�. CreateThread()�Լ��� �̿��� �۾��� �����带 �������ְ� �ֽ��ϴ�. 

bool MTServerManager::CAcceptLoop()
{
	HANDLE hThread;
	while (true){
		//���� ���� ����.
		SOCKET acceptSock = accept(mListenSocket, NULL, NULL);
		if (acceptSock == INVALID_SOCKET){
			cout << "accept error : Invalid socket..." << endl;
			continue;
		}
		SOCKADDR_IN clientAddr;
		int AddrLen = sizeof(clientAddr);
		getpeername(acceptSock, (SOCKADDR*)&clientAddr, &AddrLen);
		
		//Ŭ���̾�Ʈ ����.
		ClientSession * client = GSessionManager->CreateClient(acceptSock);

		//Ŭ������ó��.
		if (client->OnConnect(&clientAddr) == false)
		{
			cout << "connect error..." <<endl;
			client->Disconnect();
			GSessionManager->DeleteClient(client);
		}
		// thread ���� �� Ŭ���̾�Ʈ �ѱ��.
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

//�۾��� ������� ����� ������ �Լ��Դϴ�. ClientSession�� �ۼ��� �Լ��� �۵��Ǹ� Echo��ɸ� �մϴ�.

DWORD WINAPI MTServerManager::WorkerThread(LPVOID lpParam)
{
	//���޵� Ŭ���̾�Ʈ�� ����.
	ClientSession * client = (ClientSession*)lpParam;

	while (true){
		//���� ���н�
		if (client->Recv() == false){
			//Ŭ�� ����.
			GSessionManager->DeleteClient(client);
			return 1;
		}
		//�۽� ���н�
		if (client->Send() == false){
			//Ŭ�� ����.
			GSessionManager->DeleteClient(client);
			return 1;
		}
	}	return 0;
}
