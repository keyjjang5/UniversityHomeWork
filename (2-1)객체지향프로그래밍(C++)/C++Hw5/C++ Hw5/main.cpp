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
			cout << endl << i + 1 << " 번째 stack full" << endl;
	}
	int n;
	for (int i = 0; i<11; i++) 
	{
		if (a.pop(n))
			cout << n << ' ';
		else 
			cout << endl << i + 1 << " 번째 stack empty";
	}
	cout << endl;

	Accumulator acc(10);
	acc.add(5).add(6).add(7); // acc의 value 멤버가 28이 된다. 
	cout << acc.get() << endl;
	
	Book cpp("명품c++", 10000);
	Book java = cpp; // 복사 생성자 호출 
	java.set("명품자바", 120000);
	cpp.show();
	java.show();

	return 0;
}