// #include "stdafx.h"

#include "ClientSession.h"
#include "MTServerManager.h"
#include "SessionManager.h"

using namespace std;

bool ClientSession::OnConnect(SOCKADDR_IN* addr)
{
	//Ŭ���̾�Ʈ �ּ����� ȹ��.
	memcpy(&mClientAddr, addr, sizeof(SOCKADDR_IN));
	int addrlen = sizeof(SOCKADDR_IN);
	getpeername(mSocket, (SOCKADDR *)&mClientAddr, &addrlen);
	//�������� ���� ����.
	mConnected = true;
	cout << "client Connected : IP = " << inet_ntoa(mClientAddr.sin_addr) << ",  Port = " << ntohs(mClientAddr.sin_port) << endl;
	//Ŭ���̾�Ʈ ���� ����.
	GSessionManager->IncreaseClientCount();
	return true;
}

bool ClientSession::Recv()
{
	//���ӻ��� Ȯ��.
	if (!IsConnected())
		return false;
	cout << "recv in...." << endl;
	int re = 0;
	char buf[BUFSIZE];
	memset(buf, 0, BUFSIZE);
	
	//����.
	re = recv(mSocket, buf, sizeof(buf), 0);
	//Error code�߻��ϸ�
	if (re == SOCKET_ERROR)
	{
		//����ó��
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
	//���� �Ŵ������� �� ����
	GSessionManager->DecreaseClientCount();
	//���� ����
	closesocket(mSocket);
	//���Ӳ������� ���� ����.
	mConnected = false;
}
