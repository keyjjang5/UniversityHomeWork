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

// 사용해 보려했으나 실패
//typedef struct mPacketHeader
//{
//	int idSize;
//	int xSize;
//	int ySize;
//	int zSize;
//	int messageSize;
//}MyPackHeader;