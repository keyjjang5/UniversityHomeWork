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
	// 값을 입력받아서 역순 출력
	// 0을 입력하면 입력종료
	/*while (true)
	{
		char temp;
		printf("값을 입력해주세요");
		scanf("%c", &temp);
		if (temp == '0')
			break;
		stack.push(temp);
	}
	printf("\n");
	stack.printAll();*/
	
	// 예시를 그대로 출력
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

