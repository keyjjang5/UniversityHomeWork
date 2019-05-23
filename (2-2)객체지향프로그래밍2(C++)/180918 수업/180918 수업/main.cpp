#include <iostream>
#include <Windows.h>
#include <conio.h>

class Player
{
	int pos;
	char face[100];

public:
	Player(const char* face = "(^_^)", int pos = 20) : pos(pos)
	{
		strcpy(this->face, face);
	}
	void move(int inc)
	{
		pos += inc;
	}
	int getPos() const
	{
		return pos;
	}
	void checkRange(int size)
	{
		if (pos < 0)
			pos = 0;
		else if (pos > size - 1)
			pos = size - 1;
	}
	void draw(char * screen, int screenSize)
	{
		checkRange(screenSize);

		strncpy(screen + pos, face, strlen(face));
	}
};

class Enemy
{
	int pos;
	char face[100];
	char faceAttacked[100];
	int count = 10;
	bool isHit = false;

public:
	Enemy(int pos = 50, const char* face = "(*_*)", const char* faceAttacked = "(T_T)") : pos(pos)
	{
		strcpy(this->face, face);
		strcpy(this->faceAttacked, faceAttacked);
	}
	void move(int inc)
	{
		pos += inc;
	}
	int getPos() const
	{
		return pos;
	}
	void checkRange(int size)
	{
		if (pos < 0)
			pos = 0;
		else if (pos > size - 1)
			pos = size - 1;
	}
	void draw(char * screen, int screenSize)
	{
		checkRange(screenSize);

		strncpy(screen + pos, face, strlen(face));
	}
	void onHit()
	{
		isHit = true;
		count = 10;
		strcpy(face, "(T_T)");
	}
	void offHit()
	{
		isHit = false;
		strcpy(face, "(*_*)");
	}
	void decreaseCount()
	{
		count--;
	}
	bool getIsHit()
	{
		return isHit;
	}
	int getCount()
	{
		return count;
	}
	void update()
	{
		/*만약 Hit상태라면
		hitCount를 줄인다
		만약 hit상태가 끝났다면
		offHit시킨다*/
		if (isHit)
		{
			count--;
			if (count == 0)
			{
				isHit = false;
				strcpy(face, "(*_*)");
			}
		}
	}
};

class Bullet
{
	int pos = -1;
	char shape = '-';

public:
	Bullet(int playerPos) : pos(playerPos)
	{

	}
	void move(int inc)
	{
		pos += inc;
	}
	int getPos()
	{
		return pos;
	}
	void checkRange(int size)
	{
		if (pos < 0)
			pos = 0;
		else if (pos > size - 1)
			pos = size - 1;
	}
	void draw(char * screen)
	{
		screen[pos] = shape;
	}

	void update(const Player* player, const Enemy* enemy)
	{
		if (!player || !enemy)
			return;
		if (player->getPos() < enemy->getPos())
			move(1);
		else
			move(-1);
	}
};

int main()
{
	const int screenLen = 119;
	char screen[screenLen + 1 + 1];
	Player player;
	Enemy* pEnemy = nullptr;
	Bullet* pBullet = nullptr;

	while (1)
	{
		/*for (int i = 0; i < screenLen; i++)
		screen[i] = ' ';*/
		memset(screen, ' ', screenLen);


		//키입력 + 이동
		if (_kbhit())
		{
			char key = getch();

			if (key == 27)
				break;
			if (key == -32)
				key = getch();

			//printf("%d\n", key);
			switch (key)
			{
			case('a'): case(75):
				player.move(-1);
				break;

			case('d'): case(77):
				player.move(1);
				break;

			case(' '):
				if (pBullet == nullptr)
				{
					pBullet = new Bullet(player.getPos());
				}
				break;
			}
		}

		player.draw(screen, screenLen);
		enemy.draw(screen, screenLen);

		/*만일 총알을 쐈다면
			총알을 화면에 그리기
			총알이 적에 도착했다면
				총알 없애기
				적 아픈표정 짓기
			총알이 적에 도착하지 않았다면
				총알을 이동*/

		if (pBullet != nullptr)
		{
			pBullet->draw(screen);
			if (pBullet->getPos() == enemy.getPos())
			{
				enemy.onHit();
				delete pBullet;
				pBullet = nullptr;
			}
			else
			{
				pBullet->update(&player, &enemy);
			}
		}

		enemy.update();
		
		//스크린을 처음부터 그리도록만드는 것
		screen[screenLen] = '\r';
		screen[screenLen + 1] = 0;
		//적움직임 + 범위내에 있는지 체크
		printf("%s\r", screen);

		Sleep(100);
	}
	return 0;
}