#include <winsock2.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32")


BOOL GetIPAddr(char *name, IN_ADDR *addr);
BOOL GetDomainName(IN_ADDR addr, char *name);


int main(int argc, char* argv[])
{
	// Q1. �ڽ��� ��ǻ���� �̸��� ������(Domain)�� ����Ͻÿ�
	printf("COMPUTERNAME = %s\n", getenv("COMPUTERNAME"));
	printf("DOMAINNAME = %s\n", getenv("USERDOMAIN"));
	
	printf("------------------------------------\n\n");


	// �۵�����
	// Q2. ȣ��Ʈ IP �ּҰ�(16 ����), ȣ��Ʈ IP �ּҰ�(10 ����), ȣ��Ʈ�̸�, Hostent ����ü�� ���� ����
	// Hostent.cpp ���� ���� + ����
	// ������ ����ó���� ���������� �ּ�ó����
	/*if (argc < 2)
	{
	cout << "������� : >Hostent �������̸�" << endl;
	return 0;
	}*/

	// ���� �ʱ�ȭ�� ����ó�� ����
	WSADATA wsaData;
	BYTE	nMajor = 2, nMinor = 2;
	WORD	wVersionRequested = MAKEWORD(nMinor, nMajor);
	int		nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet == SOCKET_ERROR)
	{
		cout << "������ ������ �ʱ�ȭ �� �� �����ϴ�." << endl;
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != nMajor ||
		HIBYTE(wsaData.wVersion) != nMinor)
	{
		cout << "������ ���� " << nMajor << "." << nMinor << " �� ����� �� �����ϴ�." << endl;
		WSACleanup();
		return -1;
	}

	// ȣ��Ʈ ����ü �ʱ�ȭ
	struct hostent* host;
	host = gethostbyname(argv[1]);
	if (host == NULL)
	{
		cout << "���� : 'gethostbyname'" << endl;
		WSACleanup();
		return 0;
	}

	IN_ADDR addr;  /* IP �ּҸ� ������ ����ü */
	addr.s_addr = *((u_long *)(host->h_addr_list[0]));
	// ppt�� �ִ��� ���� ���
	GetIPAddr(argv[1], &addr);

	// 16���� ��¿� �ӽ�����
	char* temp = inet_ntoa(addr);

	// ȣ��Ʈ �̸� ���
	cout << "ȣ��Ʈ �̸� : \t\t" << host->h_name << endl;
	// hex : cout ���� 16���� ����� �� �� �ְ� ����
	cout << "IP �ּ�(16����) :	\t\t" << hex << inet_addr(temp) << endl;
	cout << "IP �ּ�(10����) :	\t\t" << inet_ntoa(addr) << endl;

	// ���� ���α׷��� ����
	WSACleanup();
	
	printf("------------------------------------\n\n");


	// Q3. ���� �ð��� ����Ͻÿ�. XXX�� XX�� XX�� XX�� XX�� XX���� �������� ����Ͻÿ�
	time_t now;
	time(&now);
	tm* nowLocal = localtime(&now);

	printf("%d�� %d�� %d�� %d�� %d�� %d��",
		nowLocal->tm_year + 1900,
		nowLocal->tm_mon + 1,
		nowLocal->tm_mday,
		nowLocal->tm_hour,
		nowLocal->tm_min,
		nowLocal->tm_sec);

	return 0;
}

// �������̸� > ip�ּ�
//struct hostent* gethostbyname(
//	const char name // �������̸�
//);
//
//struct hostent* gethostbyaddr(
//	const char& addr,		// ��Ʈ��ũ ����Ʈ�� ���ĵ� IP�ּ�
//	int len,				// IP�ּ��� ����
//	int type				// �ּ� ü��
//);

//struct hostent
//{
//	char*	h_name;
//	char**	h_aliases;
//	short	h_addrtype;
//	short	h_length;
//	char**	h_addr_list;
//
//#define h_addr h_addr_list[0]
//};

// ������ �̸� -> IP �ּ�
BOOL GetIPAddr(char *name, IN_ADDR *addr)
{
	// �۵��� ������ ���ɼ��� ŭ
	HOSTENT* ptr = gethostbyname(name);

	/*if (ptr == NULL) {
	err_display("gethostbyname()");
	return FALSE;
	}*/

	// ptr�� nullptr�ߴ�. > 12 line
	memcpy(addr, ptr->h_addr, ptr->h_length);
	return TRUE;
}


// IP �ּ� -> ������ �̸�
BOOL GetDomainName(IN_ADDR addr, char *name)
{
	HOSTENT *ptr = gethostbyaddr((char *)&addr,
		sizeof(addr), AF_INET);
	/*if (ptr == NULL) {
	err_display("gethostbyaddr()");
	return FALSE;
	}*/
	strcpy(name, ptr->h_name);
	return TRUE;
}