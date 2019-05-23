
int hw2()
{
	char ary[12] = { 1,3,5,7,7,7,7,8,8,9,9 };
	int target = 7;
	printf("%d\n", strlen(ary));
	printf("  | ");
	for (int i = 0; i < strlen(ary); i++)
		printf("%d ", i);
	printf("\n");
	printf("----");
	for (int i = 0; i < strlen(ary); i++)
		printf("--");
	printf("\n");

	int pos = binSearch2(ary, target);

	if (pos == -1)
		printf("검색대상이 존재하지 않습니다");
	else
		printf("%d는 ary[%d]에 있습니다", target, pos);

	return 0;
}

int binSearch2(char* ary, int target)
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
			while (1)
			{
				if (ary[now - 1] == ary[now])
					now--;

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

				if (ary[now - 1] != ary[now])
					return now;
			}
		}

		if (first == last)
			return -1;
	}
}
