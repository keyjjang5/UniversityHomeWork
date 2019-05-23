
#pragma once

class MTServerManager
{
public:
	MTServerManager();
	~MTServerManager();

	//���� �ʱ�ȭ
	bool InitServer();
	//���� ����.
	void CloseServer();

	//���� ���� �Լ�. Client ����� �������.
	bool CAcceptLoop();

private:
	//������ �Լ�
	static DWORD WINAPI WorkerThread(LPVOID lpParam);

	//������ ����.
	SOCKET	mListenSocket;
};

//�������� ����ϱ� ���� extern ������ ����.
extern MTServerManager* GMTServerManager;
