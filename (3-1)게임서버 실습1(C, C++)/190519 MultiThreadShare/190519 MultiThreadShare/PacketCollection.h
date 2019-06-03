#pragma once

// Ŭ�� -> �α��� ���� �� ������ �α��� ��û ��Ŷ
typedef struct loginPacket
{
	// User Id Length
	// User Id

	// User Password Length
	// User Password

	// User Ip
	
	// User Port
}LoginPack;

// �α��� ���� -> ���� ���� �� ������ �α��� Ȯ�� + �ΰ� ��Ŷ
typedef struct loginAccept
{
	// User Ip

	// User Port

	// User Name Length
	// User Name

	// User Level... etc
};

// �α��� ���� -> Ŭ�� �� ������ �α��� Ȯ�� ��Ŷ
typedef struct loginConfirm
{
	// Success / fail

	// GameServer Ip

	// GameServer Port
};

// Ŭ�� -> ���� ���� ä�� ���� ��Ŷ
typedef struct chatPacket
{
	// User Name Length
	// User Name

	// Send Time

	// Message Length
	// Message
};

// ���� ���� -> ��� Ŭ�� �� �����ϴ� ��ε�ĳ��Ʈ�� ��Ŷ
typedef struct broadChat
{
	// User Name Length
	// User Name

	// Send Time

	// Message Length
	// Message
};

// Ŭ�� -> ���� ������ �ڽ��� �ൿ, ��ġ ���� ������ ��Ŷ
typedef struct gamePacket
{
	// User Position X
	// User Position Y

	// User Action

	// User HP

	// User KillPoint
};

// ���Ӽ��� -> Ŭ��� �ѷ��ִ� ��Ŷ
typedef struct broadGame
{
	// User Name Length
	// User Name

	// User Position X
	// User Position Y

	// User Action

	// User HP
};