#include <iostream>
#include <string>
#include "Shape.h"
#include "Graphic.h"

using namespace std;

void main()
{
	/*Shape* p[3];
	p[0] = new Oval("빈대떡", 10, 20);
	p[1] = new Rect("찰떡", 30, 40);
	p[2] = new Triangular("토스트", 30, 40);

	for (int i = 0; i< 3; i++) {
		cout << p[i]->getName() << "넓이는 " << p[i]->getArea() << endl;
	}

	for (int i = 0; i< 3; i++) {
		delete p[i];
	}*///9-7
	
	int select = 0;
	int shapeSelect = 0;
	MyList list;
	cout << "그래픽 에디터입니다." << endl;
	
	while (1)
	{
		cout << "삽입:1, 삭제:2, 모두보기:3, 종료:4 >>" << endl;
		cin >> select;

		switch (select)
		{
		case(1):
			cout << "선:1, 원:2, 사각형:3 >>" << endl;
			cin >> shapeSelect;

			if (shapeSelect == 1)
				list.addTail(new TenLine("Line"));
			if (shapeSelect == 2)
				list.addTail(new TenCircle("Circle"));
			if (shapeSelect == 3)
				list.addTail(new TenRect("Rect"));

			break;
		case(2):
			cout << "삭제하고자 하는 도형의 인덱스 >> " << endl;
			cin >> shapeSelect;

			list.deleteAt(shapeSelect);
			break;
		case(3):
			list.printAll();

			break;
		case(4):
			exit(0);
			break;
		default:
			break;
		}
	}
}