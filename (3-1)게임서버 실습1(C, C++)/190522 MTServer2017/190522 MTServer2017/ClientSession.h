#pragma once

class ClientSession;
class SessionManager;

class ClientSession
{
public:
	ClientSession(SOCKET sock) : mSocket(sock), mConnected(false)
	{
		//�ּ� �ʱ�ȭ.
		memset(&mClientAddr, 0, sizeof(SOCKADDR_IN));
	}
	~ClientSession() {}

	//����Ȯ�� �Լ�.
	bool	OnConnect(SOCKADDR_IN* addr);
	bool	IsConnected() const { return mConnected; }

	//�����Լ�.
	bool Recv();
	//�۽��Լ�.
	bool Send(const char* buf, int len);
	bool Send();

	//���� ���� �Լ�.
	void Disconnect();

private:
	//���� ���� ����
	bool			mConnected;

	//Ŭ���̾�Ʈ ����.
	SOCKET			mSocket;

	//Ŭ���̾�Ʈ �ּ�.
	SOCKADDR_IN		mClientAddr;

	//������ ����.
	char mBuf[BUFSIZE];

	//SessionManager���� �����ϱ����� friend ����.
	friend class SessionManager;
};

