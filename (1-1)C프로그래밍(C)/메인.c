#include <stdio.h>
#include <C:\Users\keyjj\Documents\Visual Studio 2015\Projects\LogueLikeGameTest1\LogueLikeGameTest1\mapseed.h>

int map(int x, int y, int mx, int my, int dox, int doy, int dcx, int dcy, int monS, int itemS);
//int move(int mx, int my);
int mapNumber()

int main()
{
	mapNumber();
	
	map(mapNumber[0].x, mapNumber[0].y, mapNumber[0].mx, mapNumber[0].my, mapNumber[0].dox, mapNumber[0].doy,
		mapNumber[0].dcx, mapNumber[0].dcy, mapNumber[0].monsterSpon, mapNumber[0].itemSpon);
	
	//move(4,4);
		
	return 0;
}



int map(int x, int y, int mx, int my, int dox, int doy, int dcx, int dcy, int monS, int itemS)
{
	//�μ� 10��

	char movec;
	int movei = 0;

	// mx : ���� ������
	// my : ���� ������
	// x : ĳ������ ������
	// y : ĳ������ ������
	// dox : ���� ���� ������
	// doy : ���� ���� ������
	// dcx : ���� ���� ������
	// dcy : ���� ���� ������

	for (int a = 0; a < my; a++)
	{
		for (int b = 0; b < mx; b++)
		{
			if (a == dox && b == doy)
			{
				printf("��");
			}
			else if (a == dcx && b == dcy)
			{
				printf("��");
			}
			else if (a == 0 || a == mx - 1 || b == 0 || b == my - 1)
			{
				printf("��");
			}
			else if (a == y && b == x)
			{
				printf("��");
			}
			//���� ������ ������ ������ �� �ڸ�
			else
			{
				printf("��");
			}
		}

		for (;;)
		{
			movec = getch();
			do
			{
				if (movec == 'w')
				{
					movei = 1;
				}
				else if (movec == 's')
				{
					movei = 2;
				}
				else if (movec == 'a')
				{
					movei = 3;
				}
				else if (movec == 'd')
				{
					movei = 4;
				}
			} while (movei == 0);

			switch (movei)
			{
			case(1):
				y--; break;
			case(2):
				y++; break;
			case(3):
				x--; break;
			case(4):
				x++; break;
			default: break;
			}
			if (x == 0)
			{
				x++;
			}
			else if (x == mx - 1)
			{
				x--;
			}
			else if (y == 0)
			{
				y++;
			}
			else if (y == my - 1)
			{
				y--;
			}
		}
		printf("\n");
	}
}

/*int move(int mx, int my) //�����̱� ���� �Լ� �����¿� �̵��� �ִ� (wasd)
{
	char movec;
	int movei = 0;
	int x = 1, y = 1;		//ĳ����
	
	
	for(;;)
	{
		movec = getch();
		do
		{
			if (movec == 'w')
			{
				movei = 1;
			}
			else if (movec == 's')
			{
				movei = 2;
			}
			else if (movec == 'a')
			{
				movei = 3;
			}
			else if (movec == 'd')
			{
				movei = 4;
			}
		}while(movei == 0);

		switch (movei)
		{
			case(1) :
				y--; break;
			case(2) :
				y++; break;
			case(3) :
				x--; break;
			case(4) :
				x++; break;
				default : break;
		}
		if (x == 0)
		{
			x++;
		}
		else if (x == mx - 1)
		{
			x--;
		}
		else if (y == 0)
		{
			y++;
		}
		else if (y == my - 1)
		{
			y--;
		}
		map(x, y, my, mx, );

		printf("\n\n");
	}
}*/

int mapNumber()
{
	struct mapCode mapSeed[9];

	mapSeed[0].x = 5;
	mapSeed[0].y = 5;
	mapSeed[0].mx = 11;
	mapSeed[0].my = 11;
	mapSeed[0].dox = 0;
	mapSeed[0].doy = 2;
	mapSeed[0].dcx;
	mapSeed[0].dcy;
	mapSeed[0].itemSpon;
	mapSeed[0].monsterSpon;
}