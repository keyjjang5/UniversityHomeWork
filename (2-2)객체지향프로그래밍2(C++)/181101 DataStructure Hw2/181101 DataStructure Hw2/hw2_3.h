#pragma once

#include "hw2_2.h"

int precedence(char operand)
{
	switch (operand)
	{
	case('+'):
	case('-'):
		return 1;
	case('*'):
	case('/'):
		return 2;
	}
}

void infixToPostfix(char c[])
{
	Stack stack(50);
	Stack parStack(50);
	char exp[50];
	int count = 0;

	strcpy(exp, c);

	for (int i = 0; i < strlen(exp); i++)
	{
		if (exp[i] == '(')
			count++;
		if (exp[i] == ')')
		{
			count--;
			while (parStack.top != -1)
				parStack.pop();
		}

		if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
		{
			if (count > 0)
			{
				while (parStack.top != -1 && precedence(parStack.peek()) >= precedence(exp[i]))
				{
					parStack.pop();
				}
			}
			else
			{
				while (stack.top != -1 && precedence(stack.peek()) >= precedence(exp[i]))
				{
					stack.pop();
				}
			}

			if (count > 0)
				parStack.push(exp[i]);
			else
				stack.push(exp[i]);

			
		}
		else if(exp[i] != '(' && exp[i] != ')')
		{
			printf("%c", exp[i]);
		}
	}

	while (stack.top != -1)
	{
		stack.pop();
	}
	printf("\n");
}