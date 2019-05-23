#include <iostream>
#include <string>
#include "MyintStack.h"
#include "Accumulator.h"
#include "Book.h"

using namespace std;

int main()
{
	MyIntStack a;
	for (int i = 0; i<11; i++) 
	{
		if (a.push(i)) 
			cout << i << ' ';
		else 
			cout << endl << i + 1 << " ��° stack full" << endl;
	}
	int n;
	for (int i = 0; i<11; i++) 
	{
		if (a.pop(n))
			cout << n << ' ';
		else 
			cout << endl << i + 1 << " ��° stack empty";
	}
	cout << endl;

	Accumulator acc(10);
	acc.add(5).add(6).add(7); // acc�� value ����� 28�� �ȴ�. 
	cout << acc.get() << endl;
	
	Book cpp("��ǰc++", 10000);
	Book java = cpp; // ���� ������ ȣ�� 
	java.set("��ǰ�ڹ�", 120000);
	cpp.show();
	java.show();

	return 0;
}