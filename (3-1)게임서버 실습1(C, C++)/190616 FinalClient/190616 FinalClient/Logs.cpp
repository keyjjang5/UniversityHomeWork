#include "Logs.h"

void Logs::Update()
{
	
	PrintHp();
	PrintEn();
	PrintTimer();
}

void Logs::WriteLog(Message message)
{
	Borland::gotoxy(posx, posy + 2);
	switch (message)
	{
	case(Message::charge):
		ChargeEnergy();
		break;

	case(Message::attack):
		Attack();
		break;

	case(Message::firstAttack):
		FirstAttack();
		break;

	case(Message::doubleAttack):
		DoubleAttack();
		break;

	case(Message::defend):
		Defend();
		break;

	case(Message::firstDefend):
		FirstDefend();
		break;

	case(Message::doubleDefend):
		DoubleDefend();
		break;

	default:
		break;
	}

	++posy;
	if (posy >= 25)
	{
		posy = 0;
		system("cls");
	}
}

void Logs::PrintHp()
{
	Borland::gotoxy(baseX, baseY);
	printf("Hp : %d", GetHp());
}

void Logs::PrintEn()
{
	char energy[30];
	memset(energy, ' ', 30);
	energy[29] = '\0';

	Borland::gotoxy(baseX, baseY + 1);
	printf("Energy : %s", energy);
	Borland::gotoxy(baseX + 9, baseY + 1);
	for (int i = 0; i < GetEn(); i++)
	{
		printf("* ");
	}
}

void Logs::PrintTimer()
{
	// 타이머를 만든다 > 출력한다
	Timer();
	Borland::gotoxy(60, baseY);
	printf("%d", time);

	return;
}

void Logs::Timer() 
{
	++frame;
	if (frame >= 20)
	{
		frame = 0;
		--time;

		if (time <= 0)
		{
			time = 20;
			// 시간초과 패킷을 보낸다.
		}
	}
}