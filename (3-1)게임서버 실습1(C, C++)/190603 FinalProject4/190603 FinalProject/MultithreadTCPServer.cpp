#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "PacketCollection.h"

using namespace std;

#define SERVERPORT 9000
#define GAMESERVERPORT 9100
#define BUFSIZE    512

// ����
CRITICAL_SECTION cs;
int share = 0;

// �α��� ������(���� ���Ϸ� ����)
char serverUid[20] = "nickname";
char serverUpass[20] = "server";
string userId[10];
string userPass[10];

int number = 0;

void ReadData();

void ChangeShare(int i)
{
	EnterCriticalSection(&cs);
	share += i;
	LeaveCriticalSection(&cs);
	printf("Share Value : %d", share);
}

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// ����
void SwitchShare(SOCKET client_sock)
{
	// ���� �߰��� : share �� �۽�
	int temp, temp2;

	int retval;
	char buf[BUFSIZE + 1];

	itoa(share, buf, 10);

	temp = share;

	retval = send(client_sock, (char*)&temp, sizeof(int), 0);


	retval = recv(client_sock, (char*)&temp2, sizeof(int), 0);
	printf("\ntemp : %d", temp2);
	temp2 -= temp;
	ChangeShare(temp2);
	printf("üũ");

	printf("changeShare");
}

// �α��� ����
bool LoginFromClient(SOCKET& client_sock)
{
	SOCKET sock = client_sock;
	int retval;
	char temp[sizeof(LoginPack)];
	bool isLoop = false;
	bool isData = false;

	// 1. Ŭ���̾�Ʈ�� ���� ��Ŷ�� �޴´�.
	retval = recv(sock, (char*)temp, sizeof(LoginPack), 0);
	temp[sizeof(LoginPack) - 1] = '\0';
	// 2. ��Ŷ�� �����Ϳ� ���Ѵ�.
	LoginPack* tempPack;
	tempPack = (LoginPack*)temp;
	char uid[20];
	strcpy(uid, tempPack->uId);
	char upass[20];
	strcpy(upass, tempPack->uPw);
	
	// 3. �ùٸ� �α��� ������ �޾Ҵٸ� ���θ޽����� ������.
	for (int i = 0; i < number; i++)
	{
		if (strcmp(uid, userId[i].c_str()) == 0 && strcmp(upass, userPass[i].c_str()) == 0)
		{
			isData = true;
			break;
		}
	}
	if (isData)
	{
		SOCKADDR_IN serveraddr;
		ZeroMemory(&serveraddr, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = inet_addr("255.255.255.255");
		serveraddr.sin_port = htons(GAMESERVERPORT);

		LoginConfirm* confirm = new LoginConfirm;
		confirm->isLogin = true;
		confirm->serverAddr = serveraddr;

		retval = send(sock, (char*)confirm, sizeof(LoginConfirm), 0);

		//// UDP ������ ����� �װ��� ���� ���� �������� ���� ����
		//// socket()
		//SOCKET udpSock = socket(AF_INET, SOCK_DGRAM, 0);
		//if (udpSock == INVALID_SOCKET) err_quit("socket()");

		//// ��ε�ĳ���� Ȱ��ȭ
		//BOOL bEnable = TRUE;
		//retval = setsockopt(udpSock, SOL_SOCKET, SO_BROADCAST,
		//	(char *)&bEnable, sizeof(bEnable));
		//if (retval == SOCKET_ERROR) err_quit("setsockopt()");

		//// ���� �ּ� ����ü �ʱ�ȭ
		//SOCKADDR_IN remoteaddr;
		//ZeroMemory(&remoteaddr, sizeof(remoteaddr));
		//remoteaddr.sin_family = AF_INET;
		//remoteaddr.sin_addr.s_addr = inet_addr("255.255.255.255"); // ��ε� ĳ��Ʈ �ּ�
		//remoteaddr.sin_port = htons(GAMESERVERPORT);

		//// ������ ������
		//retval = sendto(sock, (char*)sock, sizeof(SOCKET), 0,
		//	(SOCKADDR *)&remoteaddr, sizeof(remoteaddr));
		//if (retval == SOCKET_ERROR) {
		//	err_display("sendto()");
		//}
		
		// 4. ���ÿ� ���Ӽ����� �÷��̾� ������ �Ѱ��ش�.
		// �α��� - Ŭ���̾�Ʈ ���� Ȯ���ϰ� �߰�

		delete confirm;

		isLoop = false;
	}
	// 3. Ʋ�� �α��� ������ �޾Ҵٸ� �źθ޽����� ������.
	else
	{
		LoginConfirm* confirm = new LoginConfirm;
		confirm->isLogin = false;

		retval = send(sock, (char*)confirm, sizeof(LoginConfirm), 0);

		delete confirm;

		isLoop = true;
	}


	return isLoop;
}

// Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR *)&clientaddr, &addrlen);

	// ȸ������ or �α��� ����
	retval = recv(client_sock, buf, sizeof(char), 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}
	bool isJoin;
	isJoin = (bool)buf[0];
	if (!isJoin)
	{
		FILE *fp;

		fp = fopen("UserData.txt", "a");

		// ID �ޱ�
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
		}

		buf[retval+1] = '\0';
		printf("�ű� ���� ID : %s\n", buf);
		fprintf(fp, buf);
		fprintf(fp, " ");

		// PassWord �ޱ�
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
		}

		buf[retval] = '\0';
		printf("�ű� ���� PassWord : %s\n", buf);
		fprintf(fp, buf);
		fprintf(fp, "\n");

		fclose(fp);

		// ȸ������ ���� �޽��� ������
		isJoin = true;
		buf[0] = isJoin;
		send(client_sock, buf, sizeof(char), 0);

		number = 0;
		ReadData();
	}
	
	// �α��� Ȯ��
	bool isLoop = false;
	do
	{
		isLoop = LoginFromClient(client_sock);
	} while (isLoop == true);
	// Ȯ��
	printf("LoginFromClient ���� �Ϸ�");

	while(1){
		// ������ �ޱ�
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if(retval == SOCKET_ERROR){
			err_display("recv()");
			break;
		}
		else if(retval == 0)
			break;

		// ���� ������ ���
		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), buf);

		// ������ ������
		retval = send(client_sock, buf, retval, 0);
		if(retval == SOCKET_ERROR){
			err_display("send()");
			break;
		}
	}

	// closesocket()
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	// ���� ����¿� ����ϴ� ����
	FILE *fp;
	fp = fopen("Log.txt", "a");

	time_t now;
	time(&now);
	tm* nowLocal = localtime(&now);

	// ���� �Է�
	fprintf(fp, "%d�� %d�� %d�� %d�� %d�� %d�� : ",
		nowLocal->tm_year + 1900,
		nowLocal->tm_mon + 1,
		nowLocal->tm_mday,
		nowLocal->tm_hour,
		nowLocal->tm_min,
		nowLocal->tm_sec);

	fprintf(fp, "[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	fclose(fp);

	return 0;
}

void ReadData()
{
	bool done = false;
	ifstream fin;
	char input;
	char filename[20] = "UserData.txt";

	int count = 0;
	


	// �α��� Ȯ�ο� ������
	char tempId[20];
	char tempPass[20];


	fin.open(filename);
	if (fin.good())
	{
		done = true;
	}
	else
	{
		// If the file does not exist or there was an issue opening it then notify the user and repeat the process.
		fin.clear();
		cout << endl;
		cout << "File " << filename << " could not be opened." << endl << endl;
	}

	fin.close();

	fin.open(filename);
	if (fin.fail() == true)
	{
		return;
	}

	fin.get(input);
	while (!fin.eof())
	{
		tempId[count] = input;
		while (1)
		{
			fin.get(input);
			if (input == ' ')
			{
				++count;
				tempId[count] = '\0';
				break;
			}
			++count;

			tempId[count] = input;
		}
		count = 0;

		// ���Ͽ��� ���� �н����� �̾Ƴ���
		fin.get(input);
		tempPass[count] = input;
		while (1)
		{
			fin.get(input);
			if (input == '\n')
			{
				++count;

				tempPass[count] = '\0';
				break;
			}
			++count;

			tempPass[count] = input;
		}
		count = 0;
		if (input == '\n')
		{
			userId[number].clear();
			userId[number].append(tempId);
			userPass[number].clear();
			userPass[number].append(tempPass);

			cout << "userId : " << userId[number] << endl;
			cout << "userPass : " << userPass[number] << endl;

			++number;
		}

		fin.get(input);
	}
}

int main(int argc, char *argv[])
{
	// criticalSection
	InitializeCriticalSection(&cs);

	// ���� ����¿� ����ϴ� ����
	FILE *fp;

	time_t now;
	time(&now);
	tm* nowLocal = localtime(&now);

	// �α��� Ȯ�ο� ������
	ReadData();


	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if(retval == SOCKET_ERROR) err_quit("listen()");

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;

	while(1){
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if(client_sock == INVALID_SOCKET){
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		
		// ���� �Է�
		fp = fopen("Log.txt", "a");
		
		fprintf(fp, "%d�� %d�� %d�� %d�� %d�� %d�� : ",
			nowLocal->tm_year + 1900,
			nowLocal->tm_mon + 1,
			nowLocal->tm_mday,
			nowLocal->tm_hour,
			nowLocal->tm_min,
			nowLocal->tm_sec);
		fprintf(fp, "[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		fclose(fp);
		
		// ȸ������ or �α��� ����
		

		// ������ ����
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);
		if(hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}

	DeleteCriticalSection(&cs);

	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}