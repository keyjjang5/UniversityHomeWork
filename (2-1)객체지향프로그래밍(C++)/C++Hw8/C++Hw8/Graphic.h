#pragma once

class TenShape
{
	std::string type;
	TenShape* p;
public:
	TenShape();
	TenShape(std::string type);
	TenShape* getPtr();
	void setPtr(TenShape* p);
	std::string getType();
};

TenShape::TenShape() : type(""), p(NULL)
{

}

TenShape::TenShape(std::string type) : type(type), p(NULL)
{

}

TenShape* TenShape::getPtr()
{
	return p;
}

void TenShape::setPtr(TenShape* p)
{
	this->p = p;
}

std::string TenShape::getType()
{
	return type;
}


class TenLine :public TenShape
{
public:
	TenLine(std::string type);
};

TenLine::TenLine(std::string type) : TenShape(type)
{

}

class TenCircle :public TenShape
{
public:
	TenCircle(std::string type);
};

TenCircle::TenCircle(std::string type) : TenShape(type)
{

}

class TenRect :public TenShape
{
public:
	TenRect(std::string type);
};

TenRect::TenRect(std::string type) : TenShape(type)
{

}

class MyList
{
	TenShape* headPtr;
	TenShape* tailPtr;
	TenShape* nowPtr;
	int count;
public:
	MyList();
	void addTail(TenShape* p);
	void printAll();
	void deleteAt(int num);
};

MyList::MyList() : headPtr(NULL), tailPtr(NULL), nowPtr(NULL), count(0)
{

}

void MyList::addTail(TenShape* p)
{
	if (count == 0)
	{
		headPtr = p;
		tailPtr = p;

		count++;
		return;
	}

	tailPtr->setPtr(p);
	tailPtr = p;
	
	count++;
}

void MyList::printAll()
{
	nowPtr = headPtr;
	for (int i = 0; i < count; i++)
	{
		std::cout << i << ": " << nowPtr->getType() << std::endl;
		nowPtr = nowPtr->getPtr();
	}
}

void MyList::deleteAt(int num)
{
	int cnt = num;
	TenShape* savedPtr = NULL;

	if (num == 0)
	{
		TenShape* savedHeadPtr = NULL;
		savedHeadPtr = headPtr;
		headPtr = headPtr->getPtr();

		count--;

		delete(savedHeadPtr);
		return;
	}

	nowPtr = headPtr;
	for (int i = 0; i < cnt-1; i++)
	{
		nowPtr = nowPtr->getPtr();
	}

	savedPtr = nowPtr;

	nowPtr = headPtr;
	for (int i = 0; i < cnt; i++)
	{
		nowPtr = nowPtr->getPtr();
	}

	savedPtr->setPtr(nowPtr->getPtr());

	count--;
	delete(nowPtr);
}