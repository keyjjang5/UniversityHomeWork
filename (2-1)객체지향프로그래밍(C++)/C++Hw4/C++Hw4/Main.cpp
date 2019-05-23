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
		cout << familyName << "가족은 다음과 같이 " << size << "명 입니다." << endl;
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
	}// 이름과 반지름 설정 
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
	Circle *p; // Circle 배열에 대한 포인터 
	int size;
public:
	CircleManager(int size):size(size)
	{
		p = new Circle[size];
	}// size 크기의 배열을 동적 생성, 사용자로부터 입력 완료 
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
				cout << circleName << "의 면적은 " << p[i].getArea();
			}
		}
		cout << endl;
	}// 사용자로부터 원의 이름을 입력받아 면적 출력 
	void searchByArea(int area)
	{
		for (int i = 0; i < size; i++)
		{
			if (p[i].getArea() > area)
			{
				cout << p[i].getName() << "의 면적은 " << p[i].getArea() << ",";
			}
		}
		cout << endl;
	}// 사용자로부터 면적을 입력받아 면적보다 큰 원의 이름 출력 
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
	cout << "원의 개수 >>";
	cin >> circleNum;
	CircleManager circleManager(circleNum);
	for (int i = 0; i < circleNum; i++)
	{
		cout << "원 " << i+1 << "의 이름과 반지름 >>";
		cin >> circleName >> radius;
		cout << endl;
		circleManager.setCircle(circleName, radius, i);
	}

	cout << "검색하고자 하는 원의 이름 >> ";
	cin >> circleName;
	circleManager.searchByName(circleName);
	cout << "최소 면적을 정수로 입력하세요 >> ";
	cin >> area;
	cout << area << "보다 큰 원을 검색합니다." << endl;
	circleManager.searchByArea(area);*/

	return 0;
}

