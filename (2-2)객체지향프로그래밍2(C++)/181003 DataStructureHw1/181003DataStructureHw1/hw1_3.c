
typedef struct doubleStack
{
	int topA;
	int topB;
	int max;
	int* stk;
}doubleStack;

int initialize(doubleStack* p, int max)
{
	p->max = max;
	p->topA = 0;
	p->topB = max;
	p->stk = NULL;
	p->stk = (int*)calloc(max, sizeof(int));
	if (p->stk == NULL)
		return 0;

}

int pushA(doubleStack* p, int value)
{
	if (p->topA >= p->max || p->topA == p->topB - 1)
		return 0;
	*(p->stk + p->topA) = value;
	p->topA++;

	return 1;
}

int pushB(doubleStack* p, int value)
{
	if (p->topB <= 0 || p->topA + 1 == p->topB)
		return 0;
	*(p->stk + p->topB) = value;
	p->topB--;

	return 1;
}

int popA(doubleStack* p)
{
	if (p->topA == 0)
		return 0;
	int revalue = *(p->stk + p->topA);
	*(p->stk + p->topA) = 0;
	p->topA--;

	return revalue;
}

int popB(doubleStack* p)
{
	if (p->topB == p->max)
		return 0;
	int revalue = *(p->stk + p->topB);
	*(p->stk + p->topB) = 0;
	p->topB++;

	return revalue;
}

int printStack(doubleStack* p)
{
	printf("앞에서 부터 시작하는 stack 값들\n");
	for (int i = 0; i < p->topA; i++)
	{
		printf("%d ", *(p->stk + i));
	}
	printf("\n");

	printf("뒤에서 부터 시작하는 stack 값들\n");
	for (int i = p->max; i > p->topB; i--)
	{
		printf("%d ", *(p->stk + i));
	}
	printf("\n");
}

int hw3()
{
	doubleStack dstack;

	initialize(&dstack, 100);

	pushA(&dstack, 1);
	pushA(&dstack, 2);
	pushA(&dstack, 3);
	pushA(&dstack, 4);

	pushB(&dstack, 10);
	pushB(&dstack, 9);

	printStack(&dstack);
	printf("\n\n");

	popA(&dstack);
	popA(&dstack);
	popA(&dstack);

	popB(&dstack);

	printStack(&dstack);

	return 0;
}