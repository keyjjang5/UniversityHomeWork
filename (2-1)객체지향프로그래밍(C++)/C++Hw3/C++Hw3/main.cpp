#include "Date.h"
#include "Random.h"
#include "SelectableRandom.h"
#include "Integer.h"
#include "Oval.h"

using namespace std;

void date()
{
	//3-2
	Date birth(2014, 3, 20);
	Date independenceDay("1945/8/15");
	independenceDay.show();
	cout << birth.getYear() << ',' << birth.getMonth() << ',' << birth.getDay() << endl;
}

void randdom()
{
	//3-5
	Random r;
	for (int i = 0; i < 10; i++)
	{
		int n = r.next();
		cout << n << ' ';
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		int n = r.nexInRange(2, 4);
		cout << n << ' ';
	}
}

void selectableRandom()
{
	//3-7
	SelectableRandom r(2);
	SelectableRandom rr(1);

	for (int i = 0; i < 10; i++)
	{
		int n = r.next();
		cout << n << ' ';
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		int n = rr.nexInRange(2, 9);
		cout << n << ' ';
	}
}

void integer()
{
	//3-8
	Integer n(30);
	cout << n.get() << ' ';
	n.set(50);
	cout << n.get() << ' ';

	Integer m("300");
	cout << m.get() << ' ';
	cout << m.isEven();
}

void oval()
{
	//3-9
	Oval a, b(3, 4);
	a.set(10, 20);
	a.show();
	cout << b.getWidth() << ", " << b.getHeight() << endl;
}

int main()
{
	date();
	randdom();
	selectableRandom();
	integer();
	oval();

	return 0;
}

