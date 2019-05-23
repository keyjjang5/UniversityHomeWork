#include <iostream>;
using namespace std;

void main()
{
	//2장 5번
	int count = 0;
	char x[100];

	x[99] = NULL;
	cout << "문자들을 입력하라(100개 미만)" << endl;
	cin.getline(x, 99, '\n');

	for (int i = 0; i < 100; i++)
	{
		if (x[i] == 'x')
		{
			count++;
		}
	}
	cout << "x의 개수는 " << count << endl;

	//2장 6번
	char fir[100];
	char sec[100];
	bool trfal[100];
	int check = 0;

	cout << "100자 미만의 글을 써주세요 : ";
	cin.getline(fir, 99, '\n');
	cout << "100자 미만의 글을 써주세요 : ";
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
		cout << "같지 않습니다" << endl;
	}
	else if (check == 0)
	{
		cout << "같습니다" << endl;
	}
}