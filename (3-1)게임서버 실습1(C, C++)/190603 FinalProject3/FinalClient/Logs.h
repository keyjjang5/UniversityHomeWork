#pragma once

#include "Player.h"
#include "PacketCollection.h"


// 다양한 로그를 원하는 위치에 쓸 수 있게 만든 클래스
class Logs : public Player
{
	int baseX;
	int baseY;

	int posx;
	int posy;

	int frame;
	int time;
public:
	Logs(char* name, int hp, int x, int y) : Player(name, hp), baseX(x), baseY(y), frame(0)
		, time(20), posx(x), posy(y)
	{

	}

	void initialize()
	{
		
	}

	void Update();

	// 원하는 위치에 포인터를 옮겨놓고 원하는 메시지를 쓰는 함수
	void WriteLog(Message message);
	// 체력을 표시함
	void PrintHp();
	// 기력을 표시함
	void PrintEn();
	// 타이머를 표시함
	void PrintTimer();

private:
	void Timer();
	
};