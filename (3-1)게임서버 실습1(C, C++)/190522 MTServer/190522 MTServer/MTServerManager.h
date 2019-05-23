#pragma once

#include <Windows.h>
#include <iostream>

#define SERVERPORT 200

class MTServerManager
{
public:
	MTServerManager();
	~MTServerManager();

	//서버 초기화
	bool InitServer();
	//서버 종료.
	void CloseServer();

	//서버 구동 함수. Client 연결과 생성담당.
	bool CAcceptLoop();

private:
	//스레드 함수
	static DWORD WINAPI WorkerThread(LPVOID lpParam);

	//서버용 소켓.
	SOCKET	mListenSocket;
};

//전역으로 사용하기 위해 extern 변수로 정의.
extern MTServerManager* GMTServerManager;
