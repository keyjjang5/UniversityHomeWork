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
	Dnode *head;	 	 // ���� ��� ��带 ����Ŵ
	Dnode *tail;	 	 // ���� ���� ��带 ����Ŵ
} DList;

// ����Ʈ���� ��� ������ ��ȯ (���� ��� ����) 
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

// ����Ʈ���� ��� �����͵��� ��� ��� �������� ��� (��, ���� �ֱ� ����� �ۺ��� ���)
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

// str ���ڿ� �����͸� �����ͷ� ���� ���� ���� ����Ʈ ��忡 ���� ���� ���� ��, ����� �ּ� �� ��ȯ
Dnode *createNode(const char *str)
{
	Dnode* newNode = (Dnode*)malloc(sizeof(Dnode));
	newNode->data = (char*)str;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

// ����Ʈ�� ������ �߰� (���� ��� ��� �ٷ� ������ �߰�) 
void insert(DList *list, const char *str)
{
	Dnode* newNode = createNode(str);
	newNode->prev = list->head;
	newNode->next = list->head->next;
	list->head->next->prev = newNode;
	list->head->next = newNode;
}

// ����Ʈ���� ��� �����͵��� ���ʴ�� �˻��ؼ� str ���� ��ġ�ϴ� ��尡 ������ 
// �ش� ����� �ּҸ� ��ȯ; ��ġ�ϴ� ��尡 ���� ��� NULL ��ȯ
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

// p �����Ͱ� ����Ű�� ��带5tl ����Ʈ���� ����; ���� ��Ȳ�� ��� ������
// �޽����� ȭ�鿡 ����ϰ� exit() �Լ��� �̿��Ͽ� ��������
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