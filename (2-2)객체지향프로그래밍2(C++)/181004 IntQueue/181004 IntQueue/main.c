#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct IntQ
{
	int max;	// array size
	int front;	// Q의 맨 앞, 초기값은 -1
	int rear;	// Q의 맨 뒤, 초기값은 -1
	int* que;	// 실제 배열기반 큐의 주소
}IntQ;

// Q 구조체 변수 멤버값들의 초기화
// 메모리 할당 성공시 TRUE 실패시 FALSE를 반환
int initializeQ(IntQ* q, int size)
{
	q->front = -1;
	q->rear = -1;
	q->que = (int*)calloc(size, sizeof(int));
	//메모리 할당 실패
	if (q->que == NULL)
	{
		q->max = 0;
		return FALSE;
	}
	q->max = size;
	return TRUE;
}

// 할당받은 메모리 해제
int terminateQ(IntQ* q)
{
	if (q->que == NULL)
		return;

	free(q->que);
	q->max = 0;

	printf("망헀다! 자폭!\n");
}

// Q가 비었는지 검사
// return TRUE(1) if Q is empty
// otherwise return FALSE(0)
int isQEmpty(IntQ* q)
{
	return (q->rear == -1 && q->front == -1) ? TRUE : FALSE;
}

// Q가  가득 찼는지 검사
// return TRUE(1) if Q is empty
// otherwise return FALSE(0)
int isQFull(IntQ* q)
{
	return (q->rear == q->max - 1 && q->rear != -1) ? TRUE : FALSE;
}

// Queue에 데이터 x를 insert
// return 0 if failed (i.e., Q is full)
// otherwise return 1
int enQueue(IntQ* q, int data)
{
	// Q가 가득 찼는지 검사
	if (isQFull(q))
		return FALSE;

	// Q가 비어있을 경우
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

// Q에서 맨 앞 데이터 값을 *temp에 저장
// 만약 Q가 비어있으면 0을 리턴
// 그렇지 않으면 1을 리턴

int deQueue(IntQ* q, int* temp)
{
	// 에러 검사
	if (isQEmpty(q))
		return FALSE;

	*temp = q->que[q->front];
	// Q가 비어있지 않고 front와 rear의 값이 같을때(데이터 개수가 1개인 경우)
	if (q->front == q->rear)	// 데이터 개수가 1
	{
		q->front = -1;
		q->rear = -1;
	}
	// Q가 비어있지 않으면 front 값을 1 증가
	else
		q->front++;

	return TRUE;
}

// Q의 데이터를 모두 출력
void printQ(IntQ* q)
{
	if (isQEmpty(q))
		return;

	for (int i = q->front;i <= q->rear;i++)
		printf("%d : %d\n", i, q->que[i]);
}

// Q 내의 데이터 개수를 return
// Q가 비었으면 0을 return
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
		printf("initializeQ 성공");
		printf("Q size : %d \n", myq.max);
		if (isQEmpty(&myq))
			printf("Q is empty \n");
		else
			printf("Q is not empty\n");
	}
	else
	{
		printf("initializeQ 실패");
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