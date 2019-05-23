#pragma once
#include <stdio.h>
#include "SinglyLinkedList.h"

Node* reverseList(List* list, Node* head)
{
	Node* reverseHead = head;
	if (head->next != NULL)
	{
		reverseHead = reverseList(list, head->next);

		head->next->next = head;
	}
	if (head == list->head)
	{
		head->next = NULL;
		list->head = reverseHead;
	}

	return reverseHead;
}

void printForward(Node* head)
{
	printf("List : %d\n", head->data);
	if (head->next != NULL)
		printForward(head->next);
}

void printReverse(Node* head)
{
	if (head->next != NULL)
		printReverse(head->next);
	printf("List : %d\n", head->data);
}