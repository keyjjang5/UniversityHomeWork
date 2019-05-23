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
//	MyPackHeader(int id, int x, int y, int z, int message)
//	{
//		idSize = id;
//		xSize = x;
//		ySize = y;
//		zSize = z;
//		messageSize = message;
//	}
//	MyPackHeader(MyPack* pack)
//	{
//		idSize = sizeof(pack->id);
//		xSize = sizeof(pack->x);
//		ySize = sizeof(pack->y);
//		zSize = sizeof(pack->z);
//		messageSize = sizeof(pack->message);
//	}
//	int idSize;
//	int xSize;
//	int ySize;
//	int zSize;
//	int messageSize;
//}MyPackHeader;