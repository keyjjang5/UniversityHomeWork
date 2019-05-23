// #include "stdafx.h"

#include "ClientSession.h"
#include "MTServerManager.h"
#include "SessionManager.h"

using namespace std;

bool ClientSession::OnConnect(SOCKADDR_IN* addr)
{
	//클라이언트 주소정보 획득.
	memcpy(&mClientAddr, addr, sizeof(SOCKADDR_IN));
	int addrlen = sizeof(SOCKADDR_IN);
	getpeername(mSocket, (SOCKADDR *)&mClientAddr, &addrlen);
	//접속으로 상태 변경.
	mConnected = true;
	cout << "client Connected : IP = " << inet_ntoa(mClientAddr.sin_addr) << ",  Port = " << ntohs(mClientAddr.sin_port) << endl;
	//클라이언트 개수 증가.
	GSessionManager->IncreaseClientCount();
	return true;
}

bool ClientSession::Recv()
{
	//접속상태 확인.
	if (!IsConnected())
		return false;
	cout << "recv in...." << endl;
	int re = 0;
	char buf[BUFSIZE];
	memset(buf, 0, BUFSIZE);
	
	//수신.
	re = recv(mSocket, buf, sizeof(buf), 0);
	//Error code발생하면
	if (re == SOCKET_ERROR)
	{
		//실패처리
		cout << "recv error.." << endl;
		return false;
	}
	buf[re] = '\0';
	memcpy(mBuf, buf, sizeof(buf));
	cout << "recv message : "<< buf << "  IP = " << inet_ntoa(mClientAddr.sin_addr) << ",  Port = " << ntohs(mClientAddr.sin_port) << endl;
	return true;
}

bool ClientSession::Send(const char* buf, int len)
{
	if (!IsConnected())
		return false;
	cout << "send in...." << endl;
	int re = 0;
	char sendBuf[BUFSIZE];
	memcpy(sendBuf, buf, len);
	re = send(mSocket, sendBuf, sizeof(sendBuf), 0);
	if (re == SOCKET_ERROR)
	{
		cout << "send error..." <<endl; 
		return false;
	}
	cout << "send message : " << sendBuf << "  IP = " << inet_ntoa(mClientAddr.sin_addr) << ",  Port = " << ntohs(mClientAddr.sin_port) << endl;
	return true;
}

bool ClientSession::Send()
{
	if (!IsConnected())
		return false;
	cout << "send in...." << endl;
	int re = 0;
	re = send(mSocket, mBuf, sizeof(mBuf), 0);
	if (re == SOCKET_ERROR)
	{
		cout << "send error..." << endl;
		return false;
	}
	cout << "send message : " << mBuf << "  IP = " << inet_ntoa(mClientAddr.sin_addr) << ",  Port = " << ntohs(mClientAddr.sin_port) << endl;
	return true;
}

void ClientSession::Disconnect()
{
	cout << "client disconnected IP = " << inet_ntoa(mClientAddr.sin_addr) << ",  Port = " << ntohs(mClientAddr.sin_port) << endl;
	//세션 매니저에서 수 감소
	GSessionManager->DecreaseClientCount();
	//소켓 종료
	closesocket(mSocket);
	//접속끊김으로 상태 변경.
	mConnected = false;
}
