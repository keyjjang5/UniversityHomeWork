#include <iostream>
#include <string>
#include "Shape.h"
#include "Graphic.h"

using namespace std;

void main()
{
	/*Shape* p[3];
	p[0] = new Oval("��붱", 10, 20);
	p[1] = new Rect("����", 30, 40);
	p[2] = new Triangular("�佺Ʈ", 30, 40);

	for (int i = 0; i< 3; i++) {
		cout << p[i]->getName() << "���̴� " << p[i]->getArea() << endl;
	}

	for (int i = 0; i< 3; i++) {
		delete p[i];
	}*///9-7
	
	int select = 0;
	int shapeSelect = 0;
	MyList list;
	cout << "�׷��� �������Դϴ�." << endl;
	
	while (1)
	{
		cout << "����:1, ����:2, ��κ���:3, ����:4 >>" << endl;
		cin >> select;

		switch (select)
		{
		case(1):
			cout << "��:1, ��:2, �簢��:3 >>" << endl;
			cin >> shapeSelect;

			if (shapeSelect == 1)
				list.addTail(new TenLine("Line"));
			if (shapeSelect == 2)
				list.addTail(new TenCircle("Circle"));
			if (shapeSelect == 3)
				list.addTail(new TenRect("Rect"));

			break;
		case(2):
			cout << "�����ϰ��� �ϴ� ������ �ε��� >> " << endl;
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