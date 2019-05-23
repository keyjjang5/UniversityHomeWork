#include "hw2_1.h"
#include "hw2_2.h"
#include "hw2_3.h"
#include "hw2_4.h"

int main()
{
    //hw2_1
    checkBalance("()");
    checkBalance(")(");
    checkBalance("{3+(2*5)}");
    checkBalance("{}");
    checkBalance("(3*4+(6)");
    checkBalance("({2+5)}");

    //hw2_2
	Stack stack(50);
	// ���� �Է¹޾Ƽ� ���� ���
	// 0�� �Է��ϸ� �Է�����
	/*while (true)
	{
		char temp;
		printf("���� �Է����ּ���");
		scanf("%c", &temp);
		if (temp == '0')
			break;
		stack.push(temp);
	}
	printf("\n");
	stack.printAll();*/
	
	// ���ø� �״�� ���
	stack.push('3');
	printf("\n");
	stack.printAll();

	stack.push('a');
	stack.push('a'); 
	stack.push('b');
	printf("\n");
	stack.printAll();

	stack.push('a');
	stack.push('a');
	stack.push('a');
	printf("\n");
	stack.printAll();

	stack.push('b');
	stack.push('a');
	stack.push('b');
	printf("\n");
	stack.printAll();
	printf("\n");

	//hw2_3
	infixToPostfix("A*(B+C)");
	infixToPostfix("(X*Y+Z)");
	printf("\n");

	//hw2_4
	sumPostfix("2");
	sumPostfix("24+");
	sumPostfix("342+/");

    return 0;
}

