#include <stdio.h>
#include <stdlib.h>
#include "SinglyLinkedList.h"
#include "DoubleLinkedList.h"
#include "Stack.h"
#include <time.h>

// B777030 ������
int main()
{
	// 1��
	/*List list;
	list.head = NULL;

	while (1)
	{
		int key = 0;
		printf("1. add\n2. delete\n3. isInList\n4. getLength\n5. isEmpty\n6. clear\n7. display\n99. exit\n");
		scanf("%d", &key);

		int item = 0;
		switch (key)
		{
		case(1):
			printf("���� �Է����ּ���.");
			scanf("%d", &item);
			add(&list, item);
			break;
		case(2):
			printf("���� �Է����ּ���.");
			scanf("%d", &item);
			deleteList(&list, item);
			break;
		case(3):
			printf("���� �Է����ּ���.");
			scanf("%d", &item);
			if (isInList(&list, item))
				printf("�����մϴ�\n");
			else
				printf("�������� �ʽ��ϴ�\n");
			break;
		case(4):
			printf("Length = %d\n", getLength(&list));
			break;
		case(5):
			if (isEmpty(&list))
				printf("����ֽ��ϴ�\n");
			else
				printf("������� �ʽ��ϴ�\n");
			break;
		case(6):
			clear(&list);
			printf("List�� Clear �Ǿ����ϴ�\n");
			break;
		case(7):
			display(&list);
			printf("List�� Display �Ǿ����ϴ�\n");
			break;
		case(99):
			printf("�����մϴ�\n");
			exit(1);
		default:
			printf("�߸��� �� �Է��Դϴ�.\n");
		}
	}*/

	// 2��
	//Dnode dummyHead;
	//Dnode dummyTail;
	//DList myList;

	//// ���� ���� ���� ���� ����� �ʱ�ȭ 
	//// �ʱ�ȭ������ ��������� �ʴ� ������ 
	//// �ʱ�ȭ ���¿��� ���� ��� ����� next ��� ������ ���� ���� ����� �ּҰ� ���� 
	//dummyHead.data = NULL;	
	//dummyHead.next = &dummyTail;
	//dummyHead.prev = NULL;

	//// �ʱ�ȭ������ ��������� �ʴ� ������ 
	//// �ʱ�ȭ ���¿��� ���� ���� ����� prev ��� ������ ���� ��� ����� �ּҰ� ���� 
	//// ��, �ʱ�ȭ ���¿��� dummyHead�� dummyTail �� ������ ���� �ּҰ��� ���� �ֵ��� ��. 
	//dummyTail.data = NULL;
	//dummyTail.next = NULL;
	//dummyTail.prev = &dummyHead;

	//myList.head = &dummyHead;
	//myList.tail = &dummyTail;

	//while (1)
	//{
	//	int key = 0;
	//	printf("1. insert\n2. remove\n3. countList\n4. printList\n99. exit\n");
	//	scanf("%d", &key);

	//	char item[100] = { NULL };
	//	switch (key)
	//	{
	//	case(1):
	//		printf("���� �Է����ּ���.");
	//		scanf("%s", &item);
	//		char* temp = (char*)malloc(sizeof(item));
	//		strcpy(temp, item);
	//		insert(&myList, temp);
	//		break;
	//	case(2):
	//		printf("���� �Է����ּ���.");
	//		scanf("%s", &item);
	//		removeList(&myList, search(&myList, item));
	//		break;
	//	case(3):
	//		printf("Length = %d\n", countList(&myList));
	//		break;
	//	case(4):
	//		printList(&myList);
	//		printf("List�� print �Ǿ����ϴ�\n");
	//		break;
	//	case(99):
	//		printf("�����մϴ�\n");
	//		exit(1);
	//	default:
	//		printf("�߸��� �� �Է��Դϴ�.\n");
	//		break;
	//	}
	//}


	// 3��
	// LinkedListStack�� ��� 3000~3500 ������ �ð��� �ҿ��
	// ArrayStack�� ��� 400~500 ������ �ð��� �ҿ��
	// �ð����̰� �������� ����
	// ù��°�� LinkedListStack �� �Ź� Push, Pop�� ���ٶ� ���� �����Ҵ�� �޸������� ���ش�.
	// �ι����� ��ǻ�� �ϵ��� Cpuĳ�ø޸𸮿� �޸𸮿��� ������ �����͸� ������ �ֺ��� �ִ�
	// ���� ���� �����ٰ� �ִµ� LinkedListStack�� ��� �̷��� �������������� �����ʾƼ� �迭����
	// ���������� �����ȴ�.

	/*IntStackArray stackArray;
	arrayStackInit(&stackArray, 100);

	clock_t start, finish;
	start = clock();

	for (int i = 0; i<10000000; i++) 
	{
		arrayStackPush(&stackArray, i);

		arrayStackPop(&stackArray);
	}

	finish = clock();

	double duration = (double)(finish - start);
	printf("start = %.4f, finish = %.4f, time = %.4f", (double)start, (double)finish, duration);*/

	/*IntStackLinkedList stackLinkedList;
	linkedListStackInit(&stackLinkedList, 100);

	clock_t start, finish;
	start = clock();

	for (int i = 0; i < 10000000; i++)
	{
		linkedListStackPush(&stackLinkedList, i);

		linkedListStackPop(&stackLinkedList);
	}

	finish = clock();

	double duration = (double)(finish - start);
	printf("start = %.4f, finish = %.4f, time = %.4f", (double)start, (double)finish, duration);*/

	return 0;
}