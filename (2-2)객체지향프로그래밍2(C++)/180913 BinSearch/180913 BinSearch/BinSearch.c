#include <stdio.h>
#include <stdlib.h>

int BinSearch(int* pA, int n, int t)
{
	pA = (int *)calloc(n, sizeof(int));

	for (int i = 0; i < n; i++)
	{
		*(pA + i) = i * 2;
	}

	int first = 0;
	int last = n - 1;
	int mid = 0;
	int count = 0;

	while (first <= last)
	{
		mid = (first + last) / 2;
		if (pA[mid] == t)
		{
			printf("%d 번 실행 했습니다", count);

			free(pA);

			return mid;
		}
		else if (pA[mid] < t)
			first = mid + 1;
		else if (pA[mid] > t)
			last = mid - 1;
		
		count++;
	}

	printf("%d 번 실행 했습니다", count);

	free(pA);

	return -1;
}


int main()
{
	int* pArray = NULL;
	int n = 1000000;
	int t = 1324;
	int print = -2;
	
	print = BinSearch(pArray, n, t);

	printf("결과값은 : %d", print);

	return 0;
}