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
	// Q1. 자신의 컴퓨터의 이름과 도메인(Domain)을 출력하시오
	printf("COMPUTERNAME = %s\n", getenv("COMPUTERNAME"));
	printf("DOMAINNAME = %s\n", getenv("USERDOMAIN"));
	
	printf("------------------------------------\n\n");


	// 작동안함
	// Q2. 호스트 IP 주소값(16 진수), 호스트 IP 주소값(10 진수), 호스트이름, Hostent 구조체를 통해 얻어옴
	// Hostent.cpp 파일 복사 + 수정
	// 무조건 예외처리로 빠져나가서 주석처리함
	/*if (argc < 2)
	{
	cout << "사용형식 : >Hostent 도메인이름" << endl;
	return 0;
	}*/

	// 소켓 초기화와 예외처리 구간
	WSADATA wsaData;
	BYTE	nMajor = 2, nMinor = 2;
	WORD	wVersionRequested = MAKEWORD(nMinor, nMajor);
	int		nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet == SOCKET_ERROR)
	{
		cout << "윈도우 소켓을 초기화 할 수 없습니다." << endl;
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != nMajor ||
		HIBYTE(wsaData.wVersion) != nMinor)
	{
		cout << "윈도우 소켓 " << nMajor << "." << nMinor << " 을 사용할 수 없습니다." << endl;
		WSACleanup();
		return -1;
	}

	// 호스트 구조체 초기화
	struct hostent* host;
	host = gethostbyname(argv[1]);
	if (host == NULL)
	{
		cout << "에러 : 'gethostbyname'" << endl;
		WSACleanup();
		return 0;
	}

	IN_ADDR addr;  /* IP 주소를 저장할 구조체 */
	addr.s_addr = *((u_long *)(host->h_addr_list[0]));
	// ppt에 있던거 만들어서 사용
	GetIPAddr(argv[1], &addr);

	// 16진수 출력용 임시저장
	char* temp = inet_ntoa(addr);

	// 호스트 이름 출력
	cout << "호스트 이름 : \t\t" << host->h_name << endl;
	// hex : cout 에서 16진수 출력을 할 수 있게 해줌
	cout << "IP 주소(16진수) :	\t\t" << hex << inet_addr(temp) << endl;
	cout << "IP 주소(10진수) :	\t\t" << inet_ntoa(addr) << endl;

	// 소켓 프로그래밍 종료
	WSACleanup();
	
	printf("------------------------------------\n\n");


	// Q3. 현재 시간을 출력하시오. XXX년 XX월 XX일 XX시 XX분 XX초의 형식으로 출력하시오
	time_t now;
	time(&now);
	tm* nowLocal = localtime(&now);

	printf("%d년 %d월 %d일 %d시 %d분 %d초",
		nowLocal->tm_year + 1900,
		nowLocal->tm_mon + 1,
		nowLocal->tm_mday,
		nowLocal->tm_hour,
		nowLocal->tm_min,
		nowLocal->tm_sec);

	return 0;
}

// 도메인이름 > ip주소
//struct hostent* gethostbyname(
//	const char name // 도메인이름
//);
//
//struct hostent* gethostbyaddr(
//	const char& addr,		// 네트워크 바이트에 정렬된 IP주소
//	int len,				// IP주소의 길이
//	int type				// 주소 체계
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

// 도메인 이름 -> IP 주소
BOOL GetIPAddr(char *name, IN_ADDR *addr)
{
	// 작동을 안했을 가능성이 큼
	HOSTENT* ptr = gethostbyname(name);

	/*if (ptr == NULL) {
	err_display("gethostbyname()");
	return FALSE;
	}*/

	// ptr이 nullptr했다. > 12 line
	memcpy(addr, ptr->h_addr, ptr->h_length);
	return TRUE;
}


// IP 주소 -> 도메인 이름
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