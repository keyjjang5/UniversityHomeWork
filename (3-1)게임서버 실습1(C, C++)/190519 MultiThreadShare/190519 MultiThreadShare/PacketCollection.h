#pragma once

// 클라 -> 로그인 서버 로 보내는 로그인 신청 패킷
typedef struct loginPacket
{
	// User Id Length
	// User Id

	// User Password Length
	// User Password

	// User Ip
	
	// User Port
}LoginPack;

// 로그인 서버 -> 게임 서버 로 보내는 로그인 확인 + 인계 패킷
typedef struct loginAccept
{
	// User Ip

	// User Port

	// User Name Length
	// User Name

	// User Level... etc
};

// 로그인 서버 -> 클라 로 보내는 로그인 확인 패킷
typedef struct loginConfirm
{
	// Success / fail

	// GameServer Ip

	// GameServer Port
};

// 클라 -> 게임 서버 채팅 전달 패킷
typedef struct chatPacket
{
	// User Name Length
	// User Name

	// Send Time

	// Message Length
	// Message
};

// 게임 서버 -> 모든 클라 로 전달하는 브로드캐스트용 패킷
typedef struct broadChat
{
	// User Name Length
	// User Name

	// Send Time

	// Message Length
	// Message
};

// 클라 -> 게임 서버로 자신의 행동, 위치 등을 보내는 패킷
typedef struct gamePacket
{
	// User Position X
	// User Position Y

	// User Action

	// User HP

	// User KillPoint
};

// 게임서버 -> 클라로 뿌려주는 패킷
typedef struct broadGame
{
	// User Name Length
	// User Name

	// User Position X
	// User Position Y

	// User Action

	// User HP
};