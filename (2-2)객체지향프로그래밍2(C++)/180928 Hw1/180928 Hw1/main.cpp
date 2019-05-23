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
	//변수 선언 : Player, EnemySpawner
	Player player("(^_^)", "(   )", 30, 10.0f);
	//Enemy enemy("(*_*)", "(T_T)", 90, 10.0f);
	Board board(0, 1, 0);
	Screen screen(100);
	EnemySpawner enemySpawner(20);
	time_t t;

	srand((unsigned)time(NULL));
	while (1)
	{
		
		//키 입력
		//만약 키 입력이 들어왔다면
			//입력을 얻어온다
			//SWITCH CASE 좌우이동, 총발사, 재장전
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
				//플레이어를 왼쪽으로 이동
				player.move(-1);
				player.setIsRight(false);
				break;

			case('d'): case(77):
				//플레이어를 오른쪽으로 이동
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
		//업데이트(Update) : 1frame마다 바뀌는 정보
		//Player
			//만약 총알을 다 쐈다면
				//2초간 장전(쏠수 없음)
			//만약 적이 근처에 있다면(2칸)
				//플레이어가 데미지를 입음
				//플레이어가 점멸함
		for (int i = 0; i < 5; i++)
		{
			if (enemySpawner.getEnemy(i) == nullptr)
				continue;
			if (enemySpawner.getEnemy(i)->getPos() > player.getPos() - 2 &&
				enemySpawner.getEnemy(i)->getPos() < player.getPos() + 7)
				player.attacked(enemySpawner.getEnemy(i)->getDamage());
		}
			//만약 체력이 0이라면
				//player가 죽음

		player.update();
		if (player.getIsSurvive());
		else if(!player.getIsSurvive())
			board.setPlay(false);

		//EnemySpawner
			//만약 몬스터가 가득찼다면
				//중단
			//만약 일정시간이 지났다면
				//남은 번호를 확인
				//남은 번호에 Enemy를 추가(동적생성)
		enemySpawner.summon(rand()%120);
		//Enemy
			//만약 플레이어가 오른쪽에 있다면
				//오른쪽으로 이동
			//만약 플레이어가 왼쪽에 있다면
				//왼쪽으로 이동
		
			//만약 공격 당했다면
				//1초간 공격당한 형태로 바꿈
				//체력이 총알의 데미지 만큼 줄어듬
			//만약 체력이 0이라면
				//Enemy가 죽음
				//Enemy의 고유값(number)을 Spawener에게 반환함
				//Score의 killCount를 증가
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
			//속도만큼 이동
			//만약 Enemy와 만났다면
				//Enemy에게 데미지만큼의 체력피해
				//Bullet소멸

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
			//level만큼 점수를 증가
		board.update();
		//Screen
			//스크린 초기화

		//그리기(Renderer)
		//Screen
			//만약 게임이 안끝났다면
				//Bullet, Enemy, Player 순으로 그림
			//만약 게임이 끝났다면
				//Score를 출력
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