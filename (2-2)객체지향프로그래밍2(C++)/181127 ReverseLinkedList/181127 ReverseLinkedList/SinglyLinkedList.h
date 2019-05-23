#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
} Node;

typedef struct list
{
	Node *head;
} List;

void add(List *list, int item) // 정렬된 리스트에 새로운 요소 추가
{
	// 추가할 노드 생성
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = item;
	newNode->next = NULL;

	// newNode가 calloc에 실패했을때 탈출
	if (newNode == NULL)
	{
		return;
	}

	// list에 값이 있는지 없는지 확인
	// 없다면 추가후 탈출

	if (list->head == NULL)
	{
		list->head = newNode;

		return;
	}

	Node* head = list->head;
	Node* tail;
	// list의 마지막 원소로 이동
	while (1)
	{
		// 마지막 원소라면 노드를 추가하고 탈출
		// 마지막 원소가 아니라면 다음으로 넘김
		if (head != NULL)
		{
			// 새로운 원소보다 클 경우 새로운 원소를 앞에 배치
			if (head->data > newNode->data)
			{
				Node* temp = head;
				newNode->next = temp;
				tail->next = newNode;
				break;
			}

			tail = head;
			head = head->next;
		}
		else
		{
			tail->next = newNode;

			break;
		}
	}
}

void deleteList(List *list, int item) // 정렬된 리스트에서 item 제거
{
	Node* head = list->head;
	// 원소가 없으면 탈출
	if (head == NULL)
		return;

	Node* temp = head;
	
	// temp가 item 일 때 제거
	if (temp->data == item)
	{
		list->head = head->next;
		free(temp);

		return;
	}

	// 첫 원소를 temp, 다음원소를 head로 설정
	head = list->head;
	temp = head;
	head = head->next;


	while (1)
	{
		if (head == NULL)
			return;

		// head가 item 일 때 제거후 탈출
		if (head->data == item)
		{
			// head->next가 NULL이 아니라면 실행 NULL 이라면 마지막이므로 실행하지 않음
			temp->next = head->next;

			free(head);
			if (temp->next != NULL)
				head = temp->next->next;
			else
				head = NULL;

			return;
		}

		temp = head;
		head = head->next;
	}
}

void clear(List *list) // 리스트의 모든 아이템 삭제
{
	Node* head = list->head;
	Node* temp = head;

	// 지우기 반복, 다지우면 탈출
	while (1)
	{
		if (temp == NULL)
			break;

		head = head->next;
		free(temp);
		temp = head;
	}

	list->head = NULL;
}

int isInList(List *list, int item) // item이 리스트 안에 있는지를 검사하여, 있으면 TRUE(1)를 리턴하고 없으면 FALSE(0)를 리턴
{
	Node* head = list->head;
	Node* temp = head;

	while (1)
	{
		if (temp == NULL)
			return 0;

		if (temp->data == item)
			return 1;

		head = head->next;
		temp = head;
	}

	return 0;
}

unsigned int getLength(List *list) // 리스트의 길이(즉, 리스트 내의 아이템 개수)를 구한다
{
	Node* head = list->head;
	int cnt = 0;

	while (1)
	{
		if (head == NULL)
			return cnt;

		head = head->next;
		cnt++;
	}
}

int isEmpty(List *list) // 리스트가 비었는지를 검사하여, 비었으면 TRUE(1)를 리턴하고 아이템이 존재하면 FALSE(0)를 리턴
{
	Node* head = list->head;
	if (head == NULL)
		return 1;

	return 0;
}

void display(List *list) // 리스트의 모든 요소를 모니터에 출력
{
	Node* head = list->head;

	while (1)
	{
		if (head == NULL)
			break;

		printf("List : %d\n", head->data);
		head = head->next;
	}
}