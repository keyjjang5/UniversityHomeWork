#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct IntQ
{
	int max;	// array size
	int front;	// Q�� �� ��, �ʱⰪ�� -1
	int rear;	// Q�� �� ��, �ʱⰪ�� -1
	int* que;	// ���� �迭��� ť�� �ּ�
}IntQ;

// Q ����ü ���� ��������� �ʱ�ȭ
// �޸� �Ҵ� ������ TRUE ���н� FALSE�� ��ȯ
int initializeQ(IntQ* q, int size)
{
	q->front = -1;
	q->rear = -1;
	q->que = (int*)calloc(size, sizeof(int));
	//�޸� �Ҵ� ����
	if (q->que == NULL)
	{
		q->max = 0;
		return FALSE;
	}
	q->max = size;
	return TRUE;
}

// �Ҵ���� �޸� ����
int terminateQ(IntQ* q)
{
	if (q->que == NULL)
		return;

	free(q->que);
	q->max = 0;

	printf("������! ����!\n");
}

// Q�� ������� �˻�
// return TRUE(1) if Q is empty
// otherwise return FALSE(0)
int isQEmpty(IntQ* q)
{
	return (q->rear == -1 && q->front == -1) ? TRUE : FALSE;
}

// Q��  ���� á���� �˻�
// return TRUE(1) if Q is empty
// otherwise return FALSE(0)
int isQFull(IntQ* q)
{
	return (q->rear == q->max - 1 && q->rear != -1) ? TRUE : FALSE;
}

// Queue�� ������ x�� insert
// return 0 if failed (i.e., Q is full)
// otherwise return 1
int enQueue(IntQ* q, int data)
{
	// Q�� ���� á���� �˻�
	if (isQFull(q))
		return FALSE;

	// Q�� ������� ���
	if (isQEmpty(q))
	{
		q->front++;
		q->rear++;
		*(q->que + q->rear) = data;
	}
	else
	{
		q->rear++;
		*(q->que + q->rear) = data;
	}

	return TRUE;
}

// Q���� �� �� ������ ���� *temp�� ����
// ���� Q�� ��������� 0�� ����
// �׷��� ������ 1�� ����

int deQueue(IntQ* q, int* temp)
{
	// ���� �˻�
	if (isQEmpty(q))
		return FALSE;

	*temp = q->que[q->front];
	// Q�� ������� �ʰ� front�� rear�� ���� ������(������ ������ 1���� ���)
	if (q->front == q->rear)	// ������ ������ 1
	{
		q->front = -1;
		q->rear = -1;
	}
	// Q�� ������� ������ front ���� 1 ����
	else
		q->front++;

	return TRUE;
}

// Q�� �����͸� ��� ���
void printQ(IntQ* q)
{
	if (isQEmpty(q))
		return;

	for (int i = q->front;i <= q->rear;i++)
		printf("%d : %d\n", i, q->que[i]);
}

// Q ���� ������ ������ return
// Q�� ������� 0�� return
int countQ(IntQ* q)
{
	int count = 0;

	if (isQEmpty(q))
		return 0;

	for (int i = q->front;i <= q->rear;i++)
		count++;


	return count;
}

int main()
{
	IntQ myq;
	int temp;

	initializeQ(&myq, SIZE);
	
	if (myq.que != NULL && myq.max != 0)
	{
		printf("initializeQ ����");
		printf("Q size : %d \n", myq.max);
		if (isQEmpty(&myq))
			printf("Q is empty \n");
		else
			printf("Q is not empty\n");
	}
	else
	{
		printf("initializeQ ����");
		printf("Q size : %d \n", myq.max);
		if (isQFull(&myq))
			printf("Q is Full \n");
		else
			printf("Q is not Full\n");
	}

	enQueue(&myq, 3);
	enQueue(&myq, 5);
	enQueue(&myq, 2);
	enQueue(&myq, -1);
	
	printQ(&myq);
	printf("count : %d\n", countQ(&myq));

	if (deQueue(&myq, &temp))
		printf("deQueue success! : %d\n", temp);
	if (deQueue(&myq, &temp))
		printf("deQueue success! : %d\n", temp);
	printf("count : %d\n", countQ(&myq));
	if (deQueue(&myq, &temp))
		printf("deQueue success! : %d\n", temp);
	if (deQueue(&myq, &temp))
		printf("deQueue success! : %d\n", temp);

	printf("count : %d\n", countQ(&myq));

	terminateQ(&myq);

	return 0;
}