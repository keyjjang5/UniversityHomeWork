#pragma once

#include <iostream>
#include <string>

using namespace std;

typedef struct StackHw2_1
{
	int top;
	int max;
	char* stk;

	StackHw2_1(int max) : top(-1), max(max)
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

bool checkBalance(string s)
{
    int bCount = 0;
    int mCount = 0;
    int sCount = 0;

	StackHw2_1 stack(50);
	for (int i = 0; i < s.size(); i++)
	{
		stack.push(s[i]);
	}

    while(true)
    {
		char c = stack.pop();
		if (c == NULL)
			break;

        if (c == '[' && mCount == 0 && sCount == 0)
            bCount++;
        if (c == '{' && sCount == 0)
            mCount++;
        if (c == '(')
            sCount++;

        if (c == ']' && mCount == 0 && sCount == 0)
            bCount--;
        if (c == '}' && sCount == 0)
            mCount--;
        if (c == ')')
            sCount--;
    }

    if (bCount == 0 && mCount == 0 && sCount == 0)
    {
        printf("Yes\n");
        return true;
    }
    else
    {
        printf("No\n");
        return false;
    }
}
