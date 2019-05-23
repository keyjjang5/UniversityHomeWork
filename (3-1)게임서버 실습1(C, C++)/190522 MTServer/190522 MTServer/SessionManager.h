#pragma once

#include <Windows.h>
#include <iostream>
#include <list>


class ClientSession;

class SessionManager
{
public:
	SessionManager() : mClientCount(0) {
		//����Ʈ �ʱ�ȭ.
		clientlist.clear();
		//�Ӱ迵�� �ʱ�ȭ
		InitializeCriticalSection(&cs);
	}
	~SessionManager();

	//Ŭ���̾�Ʈ ����.
	ClientSession * CreateClient(SOCKET sock);

	//Ŭ���̾�Ʈ ����.
	void DeleteClient(ClientSession * client);

	//��ü Ŭ���̾�Ʈ ���� ����, ����.
	int IncreaseClientCount();
	int DecreaseClientCount();

private:
	//Ŭ���̾�Ʈ ������ ����Ʈ.
	typedef list<ClientSession*> ClientList;
	ClientList clientlist;

	//��ü Ŭ���̾�Ʈ ����.
	int mClientCount;

	//Ŭ���̾�Ʈ ���� ����ȭ�� ���� �Ӱ迵��
	CRITICAL_SECTION cs;
};

//�������� ����ϱ� ���� extern ������ ����.
extern SessionManager* GSessionManager;
