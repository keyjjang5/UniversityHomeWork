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
		/*���� Hit���¶��
		hitCount�� ���δ�
		���� hit���°� �����ٸ�
		offHit��Ų��*/
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


		//Ű�Է� + �̵�
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

		/*���� �Ѿ��� ���ٸ�
			�Ѿ��� ȭ�鿡 �׸���
			�Ѿ��� ���� �����ߴٸ�
				�Ѿ� ���ֱ�
				�� ����ǥ�� ����
			�Ѿ��� ���� �������� �ʾҴٸ�
				�Ѿ��� �̵�*/

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
		
		//��ũ���� ó������ �׸����ϸ���� ��
		screen[screenLen] = '\r';
		screen[screenLen + 1] = 0;
		//�������� + �������� �ִ��� üũ
		printf("%s\r", screen);

		Sleep(100);
	}
	return 0;
}