
#include "stdafx.h"
#include "ClientSession.h"
#include "SessionManager.h"


SessionManager* GSessionManager = nullptr;

SessionManager::~SessionManager()
{
	clientlist.clear();
}

ClientSession * SessionManager::CreateClient(SOCKET sock)
{
	ClientSession* client = new ClientSession(sock);
	cout << "create ClientSession.." << endl;
//클라이언트를 리스트에 추가.
	clientlist.push_back(ClientList::value_type(client));
	return client;
}

void SessionManager::DeleteClient(ClientSession * client)
{
		//iterator를 통해 클라이언트 삭제.
	list<ClientSession*>::iterator iter;
	for (iter = clientlist.begin(); iter != clientlist.end(); ){
		if(*iter == client){
			//클라 접속 종료
			client->Disconnect();
			//리스트에서 삭제.
			iter = clientlist.erase(iter);
			cout << "client remove.." <<endl;
		}else{
			iter++;
		}
	}
}
int SessionManager::IncreaseClientCount()
{
	//임계영역 진입
	EnterCriticalSection(&cs);
	//클라이언트 개수 증가.
	mClientCount++;
	cout << "client count increase.." << endl;
	//임계영역 탈출
	LeaveCriticalSection(&cs);

	return mClientCount;
}
int SessionManager::DecreaseClientCount()
{
	EnterCriticalSection(&cs);
	mClientCount--;
	cout << "client count decrease.." << endl;
	LeaveCriticalSection(&cs);

	return mClientCount;
}
