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
		//���ϴ� ���ڿ��� ���ϴ� ��ġ�� ����
		strncpy(screen + playerPos, player, strlen(player));
		strncpy(screen + enemyPos, enemy, strlen(enemy));
		//���� �ֱٿ� �߻�� ���� ��ġ�� ǥ�� ���� ���� ������
		if (bulletPos[bulletNum - 1] > 0 && bulletPos[bulletNum - 1] < screenLen)
		{
			//��� �Ѿ��� �׸���
			for (int i = 0; i < bulletSize;i++)
			{
				//��ġ�� -1(default)�϶� �� �׸����ʴ´�
				if (bulletPos[i] == -1)
					continue;

				screen[bulletPos[i]] = '-';
				if (bulletPos[i] < enemyPos)
					bulletPos[i]++;
				else if (bulletPos[i] > enemyPos)
					bulletPos[i]--;

				//�ǰ�����
				if (bulletPos[i] == enemyPos || bulletPos[i] == enemyPos + 1)
				{
					bulletPos[i] = -1;
					//strncpy(screen + enemyPos, enemyAttacked, strlen(enemyAttacked));
					//����ǥ�� ���ӽð� ����
					attackedEmotionLife = 10;
				}
			}

			if (bulletNum == bulletSize)
			{
				bulletNum = 0;
			}
		}
		//�ǰ����� ���� ���� �׸�
		if (attackedEmotionLife > 0)
		{
			strncpy(screen + enemyPos, enemyAttacked, strlen(enemyAttacked));
			attackedEmotionLife--;
		}
		

		//��ũ���� ó������ �׸����ϸ���� ��
		screen[screenLen] = '\r';
		screen[screenLen + 1] = 0;
		//�������� + �������� �ִ��� üũ
		enemyPos += rand() % 5 - 2;
		checkRange(&enemyPos, screenLen);

		printf("%s\r", screen);

		Sleep(frameLate);
	}

	return 0;
}