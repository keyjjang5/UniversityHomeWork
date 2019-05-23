#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
	int top;
	int max;
	char* stk;

	Stack(int max) : top(-1), max(max)
	{
		stk = (char*)calloc(max, sizeof(char));
	}

	void push(char c)
	{
		if (top == max)
			return;

		top++;
		stk[top] = c;

	}

	char pop()
	{
		if (top > max || top < 0)
			return NULL;

		char temp = stk[top];
		top--;

		return temp;
	}

	char peek()
	{
		if (top > max || top < 0)
			return NULL;

		return stk[top];
	}

	void printAll()
	{
		while (top != -1)
		{
			pop();
		}
		printf("\n");
	}

};