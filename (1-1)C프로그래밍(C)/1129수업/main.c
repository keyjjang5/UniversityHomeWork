#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "power.h"
#define SIZE 10

char reverse(char *p);


//int main()
//{
//	FILE *fp = NULL;
//
//	fp = fopen("alphabet.txt", "w");
//	if (fp == NULL)
//	{
//		fprintf(stderr, "파일  alphabet.txt를 열 수 없습니다\n");
//		exit(1);
//	}
//
//	char c;
//	for (c = 'a'; c <= 'z'; c++)
//	{
//		fputc(c, fp);
//	}
//	fclose(fp);
//
//	fopen("alphabet.txt", "r");
//	
//	while((c = fgetc(fp)) != EOF)
//	{
//		putchar(c);
//	}
//
//	fclose(fp);
//
//		
//		
//		return 0;
//	
//}

//int main()
//{
//	int *p = NULL;
//	int i = 0;
//
//	p = (int *)malloc(SIZE * sizeof(int));
//	if (p == NULL)
//	{
//		printf("메모리 할당 오류\n");
//		exit(1);
//	}
//
//	for (i = 0; i < SIZE; i++)
//	{
//		p[i] = rand();
//		printf("%d   ", p[i]);
//	}
//
//	int max = p[0];
//	for (i = 1; i < SIZE; i++)
//	{
//		if (p[i] > max)
//		{
//			max = p[i];
//		}
//	}
//
//	printf("최댓값 = %d \n", max);
//	free(p);
//
//	return 0;
//}

//int main()
//{
//	int x, y;
//	printf("x의 값을 입력하시오 : ");
//	scanf("%d", &x);
//	printf("y의 값을 입력하시오 : ");
//	scanf("%d", &y);
//	printf("%d의 %d 제곱값은 %f\n", x, y, power(x,y));
//
//	return 0;
//}

//int main()
//{
//	int nansoo[6] = {0,0,0,0,0,0};
//	int random = 0;
//	time_t t;
//
//	srand(&t);
//
//	for (int i = 0; i < 1000; i++)
//	{
//		random = rand() % 6 + 1;
//		if (random == 1)
//		{
//			nansoo[0]++;
//		}
//		else if (random == 2)
//		{
//			nansoo[1]++;
//		}
//		else if (random == 3)
//		{
//			nansoo[2]++;
//		}
//		else if (random == 4)
//		{
//			nansoo[3]++;
//		}
//		else if (random == 5)
//		{
//			nansoo[4]++;
//		}
//		else if (random == 6)
//		{
//			nansoo[5]++;
//		}
//	}
//	for (int i = 0; i < 6; i++)
//	{
//		printf("%d 는 %d번 생성됨\n", i+1, nansoo[i]);
//	}
//
//	int max[2] = {0,0};
//	for (int i = 0; i < 6; i++)
//	{
//		if(max[1] <= nansoo[i])
//		{
//			max[0] = i;
//			max[1] = nansoo[i];
//		}
//	}
//
//	printf("가장 많이 출력된 %d는 %d만큼 출력되었다.\n", max[0]+1, max[1]);
//
//	return 0;
//}

//int main()
//{
//	char str[] = "Hello World";
//	reverse(str);
//	printf("%s \n", str);
//
//	return 0;
//}
//
//char reverse(char *p)
//{
//	char swap;
//
//	for (int i = 0; i < strlen(p); i++)
//	{
//		if (i == strlen(p) / 2 + 1)
//		{
//			break;
//		}
//		else
//		{
//			swap = p[i];
//			p[i] = p[strlen(p) - i - 1];
//			p[strlen(p) - i - 1] = swap;
//		}
//
//	}
//}

//int main()
//{
//	for(int k =2;k<=100;k++)
//	{
//		if(prime(k) == 1)
//		{
//			printf("%d 는 소수입니다 \n", k);
//		}
//		else
//		{
//			printf("%d 는 소수가 아닙니다 \n", k);
//		}
//	}
//}
//
//int prime(int k)
//{
//	int count = 0;
//	
//	for (int i = 1; i < k; i++)
//	{
//		if (k % i == 0)
//		{
//			count++;
//		}
//
//	}
//	if (count == 1)
//	{
//		return 1;
//	}
//	else if (count != 1)
//	{
//		return 0;
//	}
//}