#include <iostream>;

using namespace std;

void Hw1()
{
	//2�� 8�� �� ���ο� ; ���� 5���� �̸��� �����Ͽ� �Է¹޾�,
	//�� �̸��� ����� ȭ�鿡 ����ϰ� ����� �̸� �Ǻ�
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
	cout << "�Էµ� �̸��� ���� �� �̸��� \"" << saveE << "\" �Դϴ�" << endl;
}

void Hw2()
{
	//2�� 14�� Ŀ�Ǹ� �ֹ��ϴ� ���α׷�, ����������, �Ƹ޸�ī��, īǪġ��
	//�� 2000, 2300, 2500���� 20000.���� ���� ����
	char order[30];
	char orderMenu[30];
	char orderMenu2[30];
	int orderNum = 0;
	int count = 0;
	int j = 0;
	while (true)
	{
		cout << "�ֹ� ���ּ��� �մ�(���� ������ ����) : ";
		//cin.getline(order, 30, ' ');
		//strcpy(orderMenu2, order);
		//if (j == 0)
		//{
		//	for (int i = 0; 1; i++)//cin.getline���� �Է¹����Ű� �� �տ� \n�� ��� �پ��־�� ����� ã�ƺ�����
		//	//�ᱹ ã�����ϰ� �ӽ÷� ���Ƴ����ϴ�.�̤� >> cin ���� �����ϱ� �ż� cin���� ����
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
		if (strcmp(orderMenu, "����������") == 0)
		{
			cout << orderNum * 2000 << "���Դϴ�. ���ְԵ弼��" << endl;
			count += orderNum * 2000;
		}
		else if (strcmp(orderMenu, "�Ƹ޸�ī��") == 0)
		{
			cout << orderNum * 2300 << "���Դϴ�. ���ְԵ弼��" << endl;
			count += orderNum * 2300;
		}
		else if (strcmp(orderMenu, "īǪġ��") == 0)
		{
			cout << orderNum * 2500 << "���Դϴ�. ���ְԵ弼��" << endl;
			count += orderNum * 2500;
		}

		if (count >= 20000)
		{
			cout << "���� ���� �������ϴ�~" << endl << "���� �Ǹŷ��� " << count << "���Դϴ�" << endl;
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
	cout << "���ڿ� ���ڴ� ����� ����, ���������� =�� ���ּ���(�տ������� ������� ���˴ϴ�)"
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
				cout << "������� " << num[i] << endl;
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
		cout << "1~3 ���� 0 ����" << endl;
		cin >> num;
		switch (num) {
		case('1'): Hw1(); break;
		case('2'): Hw2(); break;
		case('3'): Hw3(); break;
		case('0'): exit(0);
		default: cout << "�ٽ��Է����ּ���" << endl; continue;
		}
	}
}

void main()
{
	choice(); 
}