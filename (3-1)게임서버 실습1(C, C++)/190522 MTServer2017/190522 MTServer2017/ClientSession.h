#pragma once

class ClientSession;
class SessionManager;

class ClientSession
{
public:
	ClientSession(SOCKET sock) : mSocket(sock), mConnected(false)
	{
		//주소 초기화.
		memset(&mClientAddr, 0, sizeof(SOCKADDR_IN));
	}
	~ClientSession() {}

	//연결확인 함수.
	bool	OnConnect(SOCKADDR_IN* addr);
	bool	IsConnected() const { return mConnected; }

	//수신함수.
	bool Recv();
	//송신함수.
	bool Send(const char* buf, int len);
	bool Send();

	//연결 종료 함수.
	void Disconnect();

private:
	//연결 상태 변수
	bool			mConnected;

	//클라이언트 소켓.
	SOCKET			mSocket;

	//클라이언트 주소.
	SOCKADDR_IN		mClientAddr;

	//데이터 버퍼.
	char mBuf[BUFSIZE];

	//SessionManager에서 접근하기위한 friend 선언.
	friend class SessionManager;
};

