#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Board.h"
#include "Screen.h"
#include "EnemySpawner.h"

int main()
{
	//���� ���� : Player, EnemySpawner
	Player player("(^_^)", "(   )", 30, 10.0f);
	//Enemy enemy("(*_*)", "(T_T)", 90, 10.0f);
	Board board(0, 1, 0);
	Screen screen(100);
	EnemySpawner enemySpawner(20);
	time_t t;

	srand((unsigned)time(NULL));
	while (1)
	{
		
		//Ű �Է�
		//���� Ű �Է��� ���Դٸ�
			//�Է��� ���´�
			//SWITCH CASE �¿��̵�, �ѹ߻�, ������
		if (_kbhit())
		{
			char key = getch();

			if (key == 27)
				break;
			if (key == -32)
				key = getch();

			switch (key)
			{
			case('a'): case(75):
				//�÷��̾ �������� �̵�
				player.move(-1);
				player.setIsRight(false);
				break;

			case('d'): case(77):
				//�÷��̾ ���������� �̵�
				player.move(1);
				player.setIsRight(true);
				break;

			case(' '):
				player.attack();
				getch();
				break;

			default:
				break;
			}
		}
		//������Ʈ(Update) : 1frame���� �ٲ�� ����
		//Player
			//���� �Ѿ��� �� ���ٸ�
				//2�ʰ� ����(��� ����)
			//���� ���� ��ó�� �ִٸ�(2ĭ)
				//�÷��̾ �������� ����
				//�÷��̾ ������
		for (int i = 0; i < 5; i++)
		{
			if (enemySpawner.getEnemy(i) == nullptr)
				continue;
			if (enemySpawner.getEnemy(i)->getPos() > player.getPos() - 2 &&
				enemySpawner.getEnemy(i)->getPos() < player.getPos() + 7)
				player.attacked(enemySpawner.getEnemy(i)->getDamage());
		}
			//���� ü���� 0�̶��
				//player�� ����

		player.update();
		if (player.getIsSurvive());
		else if(!player.getIsSurvive())
			board.setPlay(false);

		//EnemySpawner
			//���� ���Ͱ� ����á�ٸ�
				//�ߴ�
			//���� �����ð��� �����ٸ�
				//���� ��ȣ�� Ȯ��
				//���� ��ȣ�� Enemy�� �߰�(��������)
		enemySpawner.summon(rand()%120);
		//Enemy
			//���� �÷��̾ �����ʿ� �ִٸ�
				//���������� �̵�
			//���� �÷��̾ ���ʿ� �ִٸ�
				//�������� �̵�
		
			//���� ���� ���ߴٸ�
				//1�ʰ� ���ݴ��� ���·� �ٲ�
				//ü���� �Ѿ��� ������ ��ŭ �پ��
			//���� ü���� 0�̶��
				//Enemy�� ����
				//Enemy�� ������(number)�� Spawener���� ��ȯ��
				//Score�� killCount�� ����
		for (int i = 0; i < 5; i++)
		{
			if (enemySpawner.getEnemy(i) == nullptr)
				continue;
			if (enemySpawner.getEnemy(i)->getIsSurvive())
			{
				enemySpawner.getEnemy(i)->move(&player);
				enemySpawner.getEnemy(i)->update();
			}
			else if (!enemySpawner.getEnemy(i)->getIsSurvive())
			{
				enemySpawner.dead(i);
				board.kill();
			}
		}
		//Bullet
			//�ӵ���ŭ �̵�
			//���� Enemy�� �����ٸ�
				//Enemy���� ��������ŭ�� ü������
				//Bullet�Ҹ�

		for (int i = 0; i < 10; i++)
		{
			Bullet* playerBP = player.getBullet(i);
			if (playerBP == nullptr)
				continue;

			if (playerBP != nullptr)
				playerBP->move();

			for (int j = 0; j < 5; j++)
			{
				Enemy* enemyP = enemySpawner.getEnemy(j);
				if (enemyP == nullptr || playerBP == nullptr)
					continue;
				
				if (!playerBP->checkRange())
				{
					delete(playerBP);
					player.setNullptr(i);
					playerBP = nullptr;
				}
				if (playerBP != nullptr)
				{
					if (playerBP->getPos() == enemyP->getPos() || playerBP->getPos() == enemyP->getPos() + 1)
					{
						enemyP->attacked(playerBP->getDamage());
						delete(playerBP);
						player.setNullptr(i);
						playerBP = nullptr;
					}
				}
			}
			
		}
		
		//Score
			//level��ŭ ������ ����
		board.update();
		//Screen
			//��ũ�� �ʱ�ȭ

		//�׸���(Renderer)
		//Screen
			//���� ������ �ȳ����ٸ�
				//Bullet, Enemy, Player ������ �׸�
			//���� ������ �����ٸ�
				//Score�� ���
		if (board.onPlay())
		{
			for (int i = 0; i < 5; i++)
			{
				if (enemySpawner.getEnemy(i) == nullptr)
					continue;
				if(enemySpawner.getEnemy(i)->getIsSurvive())
					screen.draw(enemySpawner.getEnemy(i)->getPos(), strlen(enemySpawner.getEnemy(i)->getShape()),
						enemySpawner.getEnemy(i)->getShape());
			}
			if (player.getIsSurvive())
				screen.draw(player.getPos(), strlen(player.getShape()), player.getShape());

			for (int i = 0; i < 10; i++)
			{
				Bullet* playerBP = player.getBullet(i);
				if (playerBP == nullptr)
					continue;
				screen.draw(playerBP->getPos(), strlen(playerBP->getShape()), playerBP->getShape());
			}
			
		}
		else
		{
			screen.print();
			printf("Score : %d, KillCount : %d, level : %d", board.getScore(), board.getKillCount(), board.getLevel());
			exit(0);
		}

		screen.print();
	}


	return 0;
}