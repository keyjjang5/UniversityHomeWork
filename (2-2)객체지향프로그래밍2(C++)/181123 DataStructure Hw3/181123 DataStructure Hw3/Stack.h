#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct intStackArray
{
	int max;
	int top;
	int* stk;
} IntStackArray;

void arrayStackInit(IntStackArray* stack, int max)
{
	stack->stk = (int*)calloc(max, sizeof(int));
	stack->top = -1;
	stack->max = max;
}

void arrayStackPush(IntStackArray* stack, int item)
{
	stack->top++;
	stack->stk[stack->top] = item;
}

void arrayStackPop(IntStackArray* stack)
{
	if (stack->top == -1)
		return;

	stack->top--;
}

typedef struct intStackNode
{
	int data;
	struct intStackNode* prev;
} IntStackNode;

typedef struct intStackLinkedList
{
	IntStackNode* head;
	int top;
	int max;

} IntStackLinkedList;

void linkedListStackInit(IntStackLinkedList* list, int max)
{
	IntStackNode* dummyHead = (IntStackNode*)malloc(sizeof(IntStackNode));
	dummyHead->data = NULL;
	dummyHead->prev = NULL;
	list->head = dummyHead;
	list->top = 0;
	list->max = max;
}

void linkedListStackPush(IntStackLinkedList* list, int item)
{
	IntStackNode* newNode = (IntStackNode*)malloc(sizeof(IntStackNode));
	newNode->data = item;
	newNode->prev = list->head;
	list->head = newNode;
	list->top++;
}

void linkedListStackPop(IntStackLinkedList* list)
{
	IntStackNode* temp = list->head;
	list->head = list->head->prev;
	list->top--;
	free(temp);
}