#pragma once

typedef struct FloatStack
{
	int top;
	int max;
	float* stk;

	FloatStack(int max) : top(-1), max(max)
	{
		stk = (float*)calloc(max, sizeof(float));
	}

	void push(float c)
	{
		if (top == max)
			return;

		top++;
		stk[top] = c;
	}

	float pop()
	{
		if (top > max || top < 0)
			return NULL;

		float temp = stk[top];
		top--;

		return temp;
	}

	float peek()
	{
		if (top > max || top < 0)
			return NULL;

		return stk[top];
	}

	void printAll()
	{
		while (top != -1)
		{
			printf("%d", pop());
		}
	}

};


void sumPostfix(char c[])
{
	FloatStack stack(50);
	char exp[50];
	float value = 0;

	strcpy(exp, c);

	for (int i = 0; i < strlen(exp); i++)
	{
		if (exp[i] != '+' && exp[i] != '-' && exp[i] != '*' && exp[i] != '/')
		{
			stack.push(exp[i] - 48);
		}
		
		if (stack.top >= 1 && (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/'))
		{
			float temp2 = stack.pop();
			float temp1 = stack.pop();
			
			if (exp[i] == '+')
				stack.push(temp1 + temp2);
			if (exp[i] == '-')
				stack.push(temp1 - temp2);
			if (exp[i] == '*')
				stack.push(temp1 * temp2);
			if (exp[i] == '/')
				stack.push(temp1 / temp2);
		}
	}
	printf("%s", exp);
	value = stack.pop();
	printf("\n°á°ú°ª : %.2f\n", value);
}