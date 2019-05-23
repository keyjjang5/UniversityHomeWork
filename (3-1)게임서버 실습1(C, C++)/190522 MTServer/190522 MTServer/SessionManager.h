#pragma once

#include <Windows.h>
#include <iostream>
#include <list>


class ClientSession;

class SessionManager
{
public:
	SessionManager() : mClientCount(0) {
		//리스트 초기화.
		clientlist.clear();
		//임계영역 초기화
		InitializeCriticalSection(&cs);
	}
	~SessionManager();

	//클라이언트 생성.
	ClientSession * CreateClient(SOCKET sock);

	//클라이언트 삭제.
	void DeleteClient(ClientSession * client);

	//전체 클라이언트 숫자 증가, 감소.
	int IncreaseClientCount();
	int DecreaseClientCount();

private:
	//클라이언트 관리용 리스트.
	typedef list<ClientSession*> ClientList;
	ClientList clientlist;

	//전체 클라이언트 숫자.
	int mClientCount;

	//클라이언트 숫자 동기화를 위한 임계영역
	CRITICAL_SECTION cs;
};

//전역으로 사용하기 위해 extern 변수로 정의.
extern SessionManager* GSessionManager;
