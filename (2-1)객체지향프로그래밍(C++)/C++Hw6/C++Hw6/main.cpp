#include <iostream>
#include <string>
#include "MyVector.h"
#include "ArrayUtility2.h"
#include "Trace.h"

using namespace std;

void f() 
{
	int a, b, c;
	cout << "�� ���� ������ �Է��ϼ���>>";
	cin >> a >> b;
	Trace::put("f()", "������ �Է¹޾���"); // ����� ���� ���� 
	c = a + b;
	Trace::put("f()", "�� ���"); // ����� ���� ���� 
	cout << "���� " << c << endl;
}

int main()
{
	//MyVector normal;
	//MyVector special(10, 5);

	//normal.getMember();//size�� mem�� �������� �Լ�
	//special.getMember();

	/*int x[5];
	int y[5];
	int* returnValue;
	cout << "������ 5 �� �Է��϶�. �迭 x�� �����Ѵ� >>";
	for (int i = 0; i < 5; i++)
	{
		cin >> x[i];
	}
	cout << "������ 5 �� �Է��϶�. �迭 y�� �����Ѵ� >>";
	for (int i = 0; i < 5; i++)
	{
		cin >> y[i];
	}
	cout << "��ģ ���� �迭�� ����Ѵ�." << endl;
	returnValue = ArrayUtility2::concat(x, y, (sizeof(x) + sizeof(y)/4));
	for (int i = 0; i < (sizeof(x) + sizeof(y)+1)/4; i++)
		cout << returnValue[i] << " ";
	delete returnValue;
	cout << "�迭 x[]���� y[]�� �A ����� ����Ѵ�" << "������ ";
	int retSize;
	returnValue = ArrayUtility2::remove(x, y, (sizeof(x) + sizeof(y)+1)/4, retSize);
	cout << retSize << endl;
	for (int i = 0; i < retSize; i++)
		cout << returnValue[i] << " ";
	delete returnValue;*/

	Trace::put("main()", "���α׷� �����մϴ�"); // ����� ���� ���� 
	f();
	Trace::put("main()", "����"); // put()�� ù��° �Ű� ������ �±��̰� �ι�° �Ű������� ����� �����̴�. 
	Trace::print("f()"); // "f()" �±׸� ���� ����� ������ ��� ����Ѵ�. 
	Trace::print(); // ��� ����� ������ ����Ѵ�. 

	return 0;
}