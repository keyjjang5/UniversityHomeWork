#include <stdio.h>
#include <stdlib.h>
#include "SinglyLinkedList.h"
#include "DoubleLinkedList.h"
#include "Stack.h"
#include <time.h>

// B777030 정승훈
int main()
{
	// 1번
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
			printf("값을 입력해주세요.");
			scanf("%d", &item);
			add(&list, item);
			break;
		case(2):
			printf("값을 입력해주세요.");
			scanf("%d", &item);
			deleteList(&list, item);
			break;
		case(3):
			printf("값을 입력해주세요.");
			scanf("%d", &item);
			if (isInList(&list, item))
				printf("존재합니다\n");
			else
				printf("존재하지 않습니다\n");
			break;
		case(4):
			printf("Length = %d\n", getLength(&list));
			break;
		case(5):
			if (isEmpty(&list))
				printf("비어있습니다\n");
			else
				printf("비어있지 않습니다\n");
			break;
		case(6):
			clear(&list);
			printf("List가 Clear 되었습니다\n");
			break;
		case(7):
			display(&list);
			printf("List가 Display 되었습니다\n");
			break;
		case(99):
			printf("종료합니다\n");
			exit(1);
		default:
			printf("잘못된 값 입력입니다.\n");
		}
	}*/

	// 2번
	//Dnode dummyHead;
	//Dnode dummyTail;
	//DList myList;

	//// 더미 헤드와 더미 테일 노드의 초기화 
	//// 초기화하지만 사용하지는 않는 데이터 
	//// 초기화 상태에서 더미 헤드 노드의 next 멤버 값으로 더미 테일 노드의 주소값 저장 
	//dummyHead.data = NULL;	
	//dummyHead.next = &dummyTail;
	//dummyHead.prev = NULL;

	//// 초기화하지만 사용하지는 않는 데이터 
	//// 초기화 상태에서 더미 테일 노드의 prev 멤버 값으로 더미 헤드 노드의 주소값 저장 
	//// 즉, 초기화 상태에서 dummyHead와 dummyTail 두 노드들이 서로 주소값을 갖고 있도록 함. 
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
	//		printf("값을 입력해주세요.");
	//		scanf("%s", &item);
	//		char* temp = (char*)malloc(sizeof(item));
	//		strcpy(temp, item);
	//		insert(&myList, temp);
	//		break;
	//	case(2):
	//		printf("값을 입력해주세요.");
	//		scanf("%s", &item);
	//		removeList(&myList, search(&myList, item));
	//		break;
	//	case(3):
	//		printf("Length = %d\n", countList(&myList));
	//		break;
	//	case(4):
	//		printList(&myList);
	//		printf("List가 print 되었습니다\n");
	//		break;
	//	case(99):
	//		printf("종료합니다\n");
	//		exit(1);
	//	default:
	//		printf("잘못된 값 입력입니다.\n");
	//		break;
	//	}
	//}


	// 3번
	// LinkedListStack의 경우 3000~3500 사이의 시간이 소요됨
	// ArrayStack의 경우 400~500 사이의 시간이 소요됨
	// 시간차이가 벌어지는 이유
	// 첫번째는 LinkedListStack 은 매번 Push, Pop을 해줄때 마다 동적할당과 메모리해제를 해준다.
	// 두번쨰는 컴퓨터 하드웨어가 Cpu캐시메모리에 메모리에서 가져온 데이터를 넣을때 주변에 있는
	// 것을 같이 가져다가 넣는데 LinkedListStack의 경우 이러한 공간적지역성에 맞지않아서 배열보다
	// 느린것으로 생각된다.

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