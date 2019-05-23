#include <stdio.h>
#include <Windows.h>
#include <conio.h>


void checkRange(int& pos, int screenSize)
{
	if (pos < 0)
		pos = 0;
	if (pos >= screenSize)
		pos = screenSize - 1;
}
void checkRange(int *pos, int screenSize)
{
	if (*pos < 0)
		*pos = 0;
	if (*pos >= screenSize)
		*pos = screenSize - 1;
}

int main()
{
	const int screenLen = 119;
	char screen[screenLen + 1 + 1];
	char player[20] = "(^_^)";
	char enemy[20] = "(*_*)";
	char enemyAttacked[20] = "(T_T)";
	int playerPos = 30;
	int enemyPos = 90;

	const int bulletSize = 120;
	int bulletNum = 0;
	int bulletPos[bulletSize];
	for (int i = 0;i < bulletSize;i++)
		bulletPos[i] = -1;

	const int frameLate = 100;

	int attackedEmotionLife = 0;

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
				playerPos--;
				break;

			case('d'): case(77):
				playerPos++;
				break;

			case(' '):
				bulletPos[bulletNum] = playerPos;
				bulletNum++;
				break;
			}
		}



		checkRange(&playerPos, screenLen);
		//원하는 문자열을 원하는 위치에 넣음
		strncpy(screen + playerPos, player, strlen(player));
		strncpy(screen + enemyPos, enemy, strlen(enemy));
		//가장 최근에 발사된 총의 위치가 표현 범위 내에 있을때
		if (bulletPos[bulletNum - 1] > 0 && bulletPos[bulletNum - 1] < screenLen)
		{
			//모든 총알을 그린다
			for (int i = 0; i < bulletSize;i++)
			{
				//위치가 -1(default)일때 는 그리지않는다
				if (bulletPos[i] == -1)
					continue;

				screen[bulletPos[i]] = '-';
				if (bulletPos[i] < enemyPos)
					bulletPos[i]++;
				else if (bulletPos[i] > enemyPos)
					bulletPos[i]--;

				//피격판정
				if (bulletPos[i] == enemyPos || bulletPos[i] == enemyPos + 1)
				{
					bulletPos[i] = -1;
					//strncpy(screen + enemyPos, enemyAttacked, strlen(enemyAttacked));
					//감정표현 지속시간 생성
					attackedEmotionLife = 10;
				}
			}

			if (bulletNum == bulletSize)
			{
				bulletNum = 0;
			}
		}
		//피격판정 수명에 따라서 그림
		if (attackedEmotionLife > 0)
		{
			strncpy(screen + enemyPos, enemyAttacked, strlen(enemyAttacked));
			attackedEmotionLife--;
		}
		

		//스크린을 처음부터 그리도록만드는 것
		screen[screenLen] = '\r';
		screen[screenLen + 1] = 0;
		//적움직임 + 범위내에 있는지 체크
		enemyPos += rand() % 5 - 2;
		checkRange(&enemyPos, screenLen);

		printf("%s\r", screen);

		Sleep(frameLate);
	}

	return 0;
}