#include <iostream>
#include <string>


using namespace std;


void reverseSort(const string& str)
{
	//4-6
	if (str == "exit")
		exit(0);

	cout << ">>";
	for (int i = 1; i <= str.length(); i++)
	{
		cout << str.at(str.length() - i);
	}
	cout << endl;

}

void rSortControl()
{
	string str;
	while (1)
	{
		getline(cin, str, '\n');
		reverseSort(str);
	}
}

class Person
{
	string name;
public:
	Person() {}
	Person(string name) { this->name = name; }
	string getName() { return name; }
	void setName(string name) { this->name = name; }
};

class Family
{
	Person *p;
	int size;
	string familyName;
public:
	Family(const string& name, int size) :familyName(name), size(size)
	{
		p = new Person[size];
	}

	void setName(int num, const string& name)
	{
		p[num].setName(name);
	}

	void show()
	{
		cout << familyName << "������ ������ ���� " << size << "�� �Դϴ�." << endl;
		for (int i = 0; i < size; i++)
		{
			cout << p[i].getName() << "     ";
		}
		cout << endl;
	}

	~Family() 
	{
		delete[] p;
	}
};


class Circle 
{
	int radius;
	string name;
public:
	Circle():name("NULL"), radius(1)
	{

	}
	void setCircle(string name, int radius)
	{
		this->name = name;
		this->radius = radius;
	}// �̸��� ������ ���� 
	double getArea()
	{
		return radius*radius*3.14;
	}
	string getName()
	{
		return name;
	}
};

class CircleManager 
{
	Circle *p; // Circle �迭�� ���� ������ 
	int size;
public:
	CircleManager(int size):size(size)
	{
		p = new Circle[size];
	}// size ũ���� �迭�� ���� ����, ����ڷκ��� �Է� �Ϸ� 
	~CircleManager() 
	{
		delete[] p;
	}
	void setCircle(string circleName, int radius, int i)
	{
		p[i].setCircle(circleName, radius);
	}
	void searchByName(const string circleName)
	{
		for (int i = 0; i < size; i++)
		{
			if (p[i].getName() == circleName)
			{
				cout << circleName << "�� ������ " << p[i].getArea();
			}
		}
		cout << endl;
	}// ����ڷκ��� ���� �̸��� �Է¹޾� ���� ��� 
	void searchByArea(int area)
	{
		for (int i = 0; i < size; i++)
		{
			if (p[i].getArea() > area)
			{
				cout << p[i].getName() << "�� ������ " << p[i].getArea() << ",";
			}
		}
		cout << endl;
	}// ����ڷκ��� ������ �Է¹޾� �������� ū ���� �̸� ��� 
};

int main()
{
	//rSortControl();

	/*Family* simpson = new Family("Simpson", 3);
	simpson->setName(0, "Mr.Simpson");
	simpson->setName(1, "Mrs.Simpson");
	simpson->setName(2, "Bart Simpson");
	simpson->show();

	delete simpson;*/

	/*int circleNum = 0;
	string circleName;
	int radius;
	int area;
	cout << "���� ���� >>";
	cin >> circleNum;
	CircleManager circleManager(circleNum);
	for (int i = 0; i < circleNum; i++)
	{
		cout << "�� " << i+1 << "�� �̸��� ������ >>";
		cin >> circleName >> radius;
		cout << endl;
		circleManager.setCircle(circleName, radius, i);
	}

	cout << "�˻��ϰ��� �ϴ� ���� �̸� >> ";
	cin >> circleName;
	circleManager.searchByName(circleName);
	cout << "�ּ� ������ ������ �Է��ϼ��� >> ";
	cin >> area;
	cout << area << "���� ū ���� �˻��մϴ�." << endl;
	circleManager.searchByArea(area);*/

	return 0;
}

