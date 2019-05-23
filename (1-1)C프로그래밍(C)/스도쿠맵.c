#include <stdio.h>

#define X 30
#define Y 30

int main()
{
	
	int sdoqu[X][Y];
	

	
	for (int i = 0; i < X; i++)
	{
		int j;

		for (j = 0; j < Y; j++)
		{
			sdoqu[i][j] = i + j;
			if (j % 3 == 0)
			{
				printf("|");
			}
			if (i + j < 10)
			{
				printf("0%d ", sdoqu[i][j]);
	
			}
			else if (i + j >= 10)
			{
				printf("%d ", sdoqu[i][j]);
			}
			if(j == Y -1)
			{
			printf("|");
			}
		}
		printf("\n");
		
		for (j = 0; j < Y; j++)
		{
			if (i % 3 == 2)
			{
				printf("   ");
			}
			else if (j %3 == 0)
			{
				printf("|");
			}
			printf("   ");

			if (j == Y - 1)
			{
				printf("|");
			}
			if (i % 3 == 2)
			{
				for(int a = 0; a<30; a++)
				{
				printf("\b");
				}
			}
		}

		if (i % 3 == 2)
		{
			for (int k = 0; k < X *2.5; k++)
			{
				printf("--");
			}
		}
		printf("\n");

	}
	return 0;
}