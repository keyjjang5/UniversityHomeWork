#include <stdio.h>
#include <string.h>

int hw1();
int hw2();
int binSearch(char* ary, int target);
int binSearch2(char* ary, int target);

int main()
{
	hw1();

	return 0;
}

int hw1()
{
	char ary[8] = { 1, 2, 3, 5, 6, 8, 9 };
	int target = 2;

	printf("  | ");
	for (int i = 0; i < strlen(ary); i++)
		printf("%d ", i);
	printf("\n");
	printf("----");
	for (int i = 0; i < strlen(ary); i++)
		printf("--");
	printf("\n");

	int pos = binSearch(ary, target);

	if (pos == -1)
		printf("검색대상이 존재하지 않습니다");
	else
		printf("%d는 ary[%d]에 있습니다", target, pos);

	return 0;
}

int binSearch(char* ary, int target)
{
	int length = strlen(ary);
	int first = 0;
	int last = length - 1;

	while (1)
	{
		int now = (first + last) / 2;

		printf("  | ");
		for (int i = 0; i < length; i++)
		{
			if (i == first)
				printf("<-");
			else if (i == now)
				printf("+ ");
			else if (i == last)
			{
				printf("->");
				break;
			}
			else
				printf("  ");
		}
		printf("\n");
		printf("%d | ", ary[now - 1]);
		for (int i = 0; i < length; i++)
		{
			printf("%d ", ary[i]);
		}
		printf("\n");

		if (target > ary[now])
		{
			first = now + 1;
			continue;
		}
		else if (target < ary[now])
		{
			last = now - 1;
			continue;
		}
		else if (target == ary[now])
		{
			return now;
		}

		if (first == last)
			return -1;
	}
}

