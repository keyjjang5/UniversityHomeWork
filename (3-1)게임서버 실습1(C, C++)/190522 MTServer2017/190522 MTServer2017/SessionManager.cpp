
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
//Ŭ���̾�Ʈ�� ����Ʈ�� �߰�.
	clientlist.push_back(ClientList::value_type(client));
	return client;
}

void SessionManager::DeleteClient(ClientSession * client)
{
		//iterator�� ���� Ŭ���̾�Ʈ ����.
	list<ClientSession*>::iterator iter;
	for (iter = clientlist.begin(); iter != clientlist.end(); ){
		if(*iter == client){
			//Ŭ�� ���� ����
			client->Disconnect();
			//����Ʈ���� ����.
			iter = clientlist.erase(iter);
			cout << "client remove.." <<endl;
		}else{
			iter++;
		}
	}
}
int SessionManager::IncreaseClientCount()
{
	//�Ӱ迵�� ����
	EnterCriticalSection(&cs);
	//Ŭ���̾�Ʈ ���� ����.
	mClientCount++;
	cout << "client count increase.." << endl;
	//�Ӱ迵�� Ż��
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
