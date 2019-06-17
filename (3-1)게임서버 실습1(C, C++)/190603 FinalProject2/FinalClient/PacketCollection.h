#pragma once
#include <Windows.h>
#include <WinSock2.h>

// 클라 -> 로그인 서버 로 보내는 로그인 신청 패킷
typedef struct loginPacket
{
	// User Id Length
	int idLength;
	// User Id
	char uId[20];

	// User Password Length
	int pwLength;
	// User Password
	char uPw[20];

	// User Ip
	// User Port
	SOCKADDR_IN addr;
}LoginPack;

// 로그인 서버 -> 게임 서버 로 보내는 로그인 확인 + 인계 패킷
typedef struct loginAccept
{
	int check;
	// User Ip
	// User Port
	SOCKADDR_IN userAddr;

	// User Name Length
	int nameLength;
	// User Name
	char name[20];

	// User Level... etc
}LoginAccept;

// 로그인 서버 -> 클라 로 보내는 로그인 확인 패킷
typedef struct loginConfirm
{
	// Success / fail
	// 로그인이 가능한가?
	bool isLogin;

	// GameServer Ip
	// GameServer Port
	SOCKADDR_IN serverAddr;
}LoginConfirm;

// 클라 -> 게임 서버 채팅 전달 패킷
typedef struct chatPacket
{
	// User Name Length // 생략 가능
	// User Name // 생략 가능

	// Send Time
	time_t time;

	// Message Length
	int messageLength;
	// Message
	char message[200];
}ChatPack;

// 게임 서버 -> 모든 클라 로 전달하는 브로드캐스트용 패킷
typedef struct broadChat
{
	// User Name Length
	int nameLength;
	// User Name
	char name[20];

	// Send Time
	time_t time;

	// Message Length
	int messageLength;
	// Message
	char message[200];
}BroadChat;

// 클라 -> 게임 서버로 자신의 행동, 위치 등을 보내는 패킷
typedef struct gamePacket
{
	// User Position X
	int posX;
	// User Position Y
	int posY;

	// User Action
	// enum을 사용해서 사용할 예정
	int action;

	// User Collision
	bool collision;

	// User HP
	int hp;

	// User KillPoint
	int killPoint;
}GamePack;

// 게임서버 -> 클라로 뿌려주는 패킷
typedef struct broadGame
{
	// User Name Length
	int nameLength;
	// User Name
	char name[20];

	// User Position X
	int posX;
	// User Position Y
	int posY;

	// User Action
	// enum을 사용해서 사용할 예정
	int action;

	// User Collision
	bool collision;

	// User HP
	int hp;
}BroadGame;