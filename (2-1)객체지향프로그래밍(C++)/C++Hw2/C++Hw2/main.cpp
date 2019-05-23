#include <iostream>;

using namespace std;

void Hw1()
{
	//2장 8번 한 라인에 ; 으로 5개의 이름을 구분하여 입력받아,
	//각 이름을 끊어내어 화면에 출력하고 가장긴 이름 판별
	char name[100] = { NULL };
	char save[20] = { NULL };
	char saveE[20] = { NULL };
	int check = 0;

	for (int i = 0; i < 5; i++)
	{
		cin.getline(name, 100, ';');
		strcpy(save, name);
		if (check <= strlen(save))
		{
			check = strlen(save);
			strcpy(saveE, save);
		}
	}
	cout << "입력된 이름중 가장 긴 이름은 \"" << saveE << "\" 입니다" << endl;
}

void Hw2()
{
	//2장 14번 커피를 주문하는 프로그램, 에스프레소, 아메리카노, 카푸치노
	//각 2000, 2300, 2500원임 20000.원을 벌면 종료
	char order[30];
	char orderMenu[30];
	char orderMenu2[30];
	int orderNum = 0;
	int count = 0;
	int j = 0;
	while (true)
	{
		cout << "주문 해주세요 손님(종류 갯수로 기입) : ";
		//cin.getline(order, 30, ' ');
		//strcpy(orderMenu2, order);
		//if (j == 0)
		//{
		//	for (int i = 0; 1; i++)//cin.getline으로 입력받은거가 맨 앞에 \n이 계속 붙어있었어서 방법을 찾아봤으나
		//	//결국 찾지못하고 임시로 막아놨습니다.ㅜㅜ >> cin 으로 받으니까 돼서 cin으로 변경
		//	{
		//		if (orderMenu2[i] != NULL)
		//		{
		//			orderMenu[i] = orderMenu2[i + 1];
		//		}
		//		else
		//		{
		//			j = 1;
		//			break;
		//		}
		//	}
		//}
		//cin.getline(order, 30, '\n');
		//orderNum = atoi(order);
		cin >> orderMenu >> orderNum;
		if (strcmp(orderMenu, "에스프레소") == 0)
		{
			cout << orderNum * 2000 << "원입니다. 맛있게드세요" << endl;
			count += orderNum * 2000;
		}
		else if (strcmp(orderMenu, "아메리카노") == 0)
		{
			cout << orderNum * 2300 << "원입니다. 맛있게드세요" << endl;
			count += orderNum * 2300;
		}
		else if (strcmp(orderMenu, "카푸치노") == 0)
		{
			cout << orderNum * 2500 << "원입니다. 맛있게드세요" << endl;
			count += orderNum * 2500;
		}

		if (count >= 20000)
		{
			cout << "오늘 영업 끝났습니다~" << endl << "오늘 판매량은 " << count << "원입니다" << endl;
			break;
		}
	}
}

void Hw3()
{
	char op[10] = { NULL };
	char sum[100] = { NULL };
	char *split = { NULL };
	int num[10] = { NULL };
	int test = 0;
	cout << "숫자와 문자는 띄어쓰기로 구분, 마지막에는 =을 써주세요(앞에서부터 순서대로 계산됩니다)"
		<< "ex)4 + 5 = " << endl;
	while (true)
	{
		cout << "? ";

		cin.getline(sum, 100, '\n');
		split = strtok(sum, " ");
		for (int i = 0; split != NULL; i++)
		{

			if (i % 2 == 0)
			{
				num[(i / 2)] = atoi(split);	

			}
			else if (i % 2 == 1)
			{
				op[((i - 1) / 2)] = *split;
				if (op[((i - 1) / 2)] == '=')
				{

					break;
				}
			}
			split = strtok(NULL, " ");
		}

		for (int i = 0; i < 10; i++)
		{
			if (op[i - 1] == '=')
			{
				break;
			}
			switch (op[i])
			{
			case('+'):
				num[i + 1] = num[i] + num[i + 1];
				break;
			case('-'):
				num[i + 1] = num[i] - num[i + 1];
				break;
			case('*'):
				num[i + 1] = num[i] * num[i + 1];
				break;
			case('/'):
				num[i + 1] = num[i] / num[i + 1];
				break;
			case('%'):
				num[i + 1] = num[i] % num[i + 1];
				break;
			case('='):
				cout << "결과값은 " << num[i] << endl;
				break;
			default:
				break;
			}
		}
	}
}

void choice()
{
	while (true)
	{
		char num = '0';
		cout << "1~3 문제 0 종료" << endl;
		cin >> num;
		switch (num) {
		case('1'): Hw1(); break;
		case('2'): Hw2(); break;
		case('3'): Hw3(); break;
		case('0'): exit(0);
		default: cout << "다시입력해주세요" << endl; continue;
		}
	}
}

void main()
{
	choice(); 
}