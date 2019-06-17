#pragma once
#include <Windows.h>
#include <WinSock2.h>

// Ŭ�� -> �α��� ���� �� ������ �α��� ��û ��Ŷ
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

// �α��� ���� -> ���� ���� �� ������ �α��� Ȯ�� + �ΰ� ��Ŷ
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

// �α��� ���� -> Ŭ�� �� ������ �α��� Ȯ�� ��Ŷ
typedef struct loginConfirm
{
	// Success / fail
	// �α����� �����Ѱ�?
	bool isLogin;

	// GameServer Ip
	// GameServer Port
	SOCKADDR_IN serverAddr;
}LoginConfirm;

// Ŭ�� -> ���� ���� ä�� ���� ��Ŷ
typedef struct chatPacket
{
	// User Name Length // ���� ����
	// User Name // ���� ����

	// Send Time
	time_t time;

	// Message Length
	int messageLength;
	// Message
	char message[200];
}ChatPack;

// ���� ���� -> ��� Ŭ�� �� �����ϴ� ��ε�ĳ��Ʈ�� ��Ŷ
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

// Ŭ�� -> ���� ������ �ڽ��� �ൿ, ��ġ ���� ������ ��Ŷ
typedef struct gamePacket
{
	// User Position X
	int posX;
	// User Position Y
	int posY;

	// User Action
	// enum�� ����ؼ� ����� ����
	int action;

	// User Collision
	bool collision;

	// User HP
	int hp;

	// User KillPoint
	int killPoint;
}GamePack;

// ���Ӽ��� -> Ŭ��� �ѷ��ִ� ��Ŷ
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
	// enum�� ����ؼ� ����� ����
	int action;

	// User Collision
	bool collision;

	// User HP
	int hp;
}BroadGame;