#include <iostream>;
using namespace std;

void main()
{
	//2�� 5��
	int count = 0;
	char x[100];

	x[99] = NULL;
	cout << "���ڵ��� �Է��϶�(100�� �̸�)" << endl;
	cin.getline(x, 99, '\n');

	for (int i = 0; i < 100; i++)
	{
		if (x[i] == 'x')
		{
			count++;
		}
	}
	cout << "x�� ������ " << count << endl;

	//2�� 6��
	char fir[100];
	char sec[100];
	bool trfal[100];
	int check = 0;

	cout << "100�� �̸��� ���� ���ּ��� : ";
	cin.getline(fir, 99, '\n');
	cout << "100�� �̸��� ���� ���ּ��� : ";
	cin.getline(sec, 99, '\n');
	for (int i = 0; i < 100; i++)
	{
		if (fir[i] == sec[i])
		{
			trfal[i] = true;
		}
		else
		{
			trfal[i] = false;
			check = 1;
			break;
		}
	}

	if (check == 1)
	{
		cout << "���� �ʽ��ϴ�" << endl;
	}
	else if (check == 0)
	{
		cout << "�����ϴ�" << endl;
	}
}