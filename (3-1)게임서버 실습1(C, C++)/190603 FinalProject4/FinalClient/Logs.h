#pragma once

#include "Player.h"
#include "PacketCollection.h"


// �پ��� �α׸� ���ϴ� ��ġ�� �� �� �ְ� ���� Ŭ����
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

	// ���ϴ� ��ġ�� �����͸� �Űܳ��� ���ϴ� �޽����� ���� �Լ�
	void WriteLog(Message message);
	// ü���� ǥ����
	void PrintHp();
	// ����� ǥ����
	void PrintEn();
	// Ÿ�̸Ӹ� ǥ����
	void PrintTimer();

private:
	void Timer();
	
};