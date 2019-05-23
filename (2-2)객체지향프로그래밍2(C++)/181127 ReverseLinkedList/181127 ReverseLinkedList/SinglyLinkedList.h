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

void add(List *list, int item) // ���ĵ� ����Ʈ�� ���ο� ��� �߰�
{
	// �߰��� ��� ����
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = item;
	newNode->next = NULL;

	// newNode�� calloc�� ���������� Ż��
	if (newNode == NULL)
	{
		return;
	}

	// list�� ���� �ִ��� ������ Ȯ��
	// ���ٸ� �߰��� Ż��

	if (list->head == NULL)
	{
		list->head = newNode;

		return;
	}

	Node* head = list->head;
	Node* tail;
	// list�� ������ ���ҷ� �̵�
	while (1)
	{
		// ������ ���Ҷ�� ��带 �߰��ϰ� Ż��
		// ������ ���Ұ� �ƴ϶�� �������� �ѱ�
		if (head != NULL)
		{
			// ���ο� ���Һ��� Ŭ ��� ���ο� ���Ҹ� �տ� ��ġ
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

void deleteList(List *list, int item) // ���ĵ� ����Ʈ���� item ����
{
	Node* head = list->head;
	// ���Ұ� ������ Ż��
	if (head == NULL)
		return;

	Node* temp = head;
	
	// temp�� item �� �� ����
	if (temp->data == item)
	{
		list->head = head->next;
		free(temp);

		return;
	}

	// ù ���Ҹ� temp, �������Ҹ� head�� ����
	head = list->head;
	temp = head;
	head = head->next;


	while (1)
	{
		if (head == NULL)
			return;

		// head�� item �� �� ������ Ż��
		if (head->data == item)
		{
			// head->next�� NULL�� �ƴ϶�� ���� NULL �̶�� �������̹Ƿ� �������� ����
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

void clear(List *list) // ����Ʈ�� ��� ������ ����
{
	Node* head = list->head;
	Node* temp = head;

	// ����� �ݺ�, ������� Ż��
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

int isInList(List *list, int item) // item�� ����Ʈ �ȿ� �ִ����� �˻��Ͽ�, ������ TRUE(1)�� �����ϰ� ������ FALSE(0)�� ����
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

unsigned int getLength(List *list) // ����Ʈ�� ����(��, ����Ʈ ���� ������ ����)�� ���Ѵ�
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

int isEmpty(List *list) // ����Ʈ�� ��������� �˻��Ͽ�, ������� TRUE(1)�� �����ϰ� �������� �����ϸ� FALSE(0)�� ����
{
	Node* head = list->head;
	if (head == NULL)
		return 1;

	return 0;
}

void display(List *list) // ����Ʈ�� ��� ��Ҹ� ����Ϳ� ���
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