#pragma once
#define BUFSIZE    50
typedef struct mPacket
{
	int id; // user id
	int x;
	int y;
	int z;

	char message[BUFSIZE];
}MyPack;

// ����� ���������� ����
//typedef struct mPacketHeader
//{
//	int idSize;
//	int xSize;
//	int ySize;
//	int zSize;
//	int messageSize;
//}MyPackHeader;