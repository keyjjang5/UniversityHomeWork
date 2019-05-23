#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dnode {
	char *data;
	struct Dnode *next;
	struct Dnode *prev;
} Dnode;

typedef struct Dlist {
	Dnode *head;	 	 // 더미 헤드 노드를 가리킴
	Dnode *tail;	 	 // 더미 테일 노드를 가리킴
} DList;

// 리스트내의 노드 개수를 반환 (더미 노드 제외) 
unsigned int countList(DList *list) 
{
	int cnt = 0;
	Dnode* temp = list->head;

	while (1)
	{
		if (temp == list->tail)
			return cnt - 1;

		temp = temp->next;
		cnt++;
	}
}

// 리스트내의 노드 데이터들을 헤드 노드 다음부터 출력 (즉, 가장 최근 사용한 앱부터 출력)
void printList(DList *list)
{
	Dnode* temp = list->head;
	temp = temp->next;
	while (1)
	{
		if (temp == list->tail)
			return;
		printf("List : %s\n", temp->data);
		temp = temp->next;
	}
}

// str 문자열 포인터를 데이터로 갖는 이중 연결 리스트 노드에 대해 동적 생성 후, 노드의 주소 값 반환
Dnode *createNode(const char *str)
{
	Dnode* newNode = (Dnode*)malloc(sizeof(Dnode));
	newNode->data = (char*)str;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

// 리스트에 데이터 추가 (더미 헤드 노드 바로 다음에 추가) 
void insert(DList *list, const char *str)
{
	Dnode* newNode = createNode(str);
	newNode->prev = list->head;
	newNode->next = list->head->next;
	list->head->next->prev = newNode;
	list->head->next = newNode;
}

// 리스트내의 노드 데이터들을 차례대로 검색해서 str 값과 일치하는 노드가 있으면 
// 해당 노드의 주소를 반환; 일치하는 노드가 없을 경우 NULL 반환
Dnode *search(DList *list, const char *str)
{
	if (str == NULL)
		return NULL;

	Dnode* temp = list->head;
	while (1)
	{
		if (temp == list->tail)
			return NULL;

		if (!strcmp(temp->next->data, str))
		{
			return temp->next;
		}

		temp = temp->next;
	}
}

// p 포인터가 가리키는 노드를5tl 리스트에서 삭제; 오류 상황의 경우 적절한
// 메시지를 화면에 출력하고 exit() 함수를 이용하여 빠져나감
void removeList(DList *list, Dnode *p)
{
	Dnode* temp = list->head;
	while (1)
	{
		if (temp == NULL)
			return;

		Dnode* temp2 = temp;
		if (temp == p)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp->data);
			free(temp);

			return;
		}
		temp = temp2;
		temp = temp->next;
	}
}