#pragma once

class Shape
{
protected:
	std::string name; // ������ �̸� 
	int width, height; // ������ �����ϴ� �簢���� �ʺ�� ���� 

public:
	Shape(const std::string n = "", int w = 0, int h = 0) : name(n), width(w), height(h) {}
	virtual double getArea() { return 0; } // dummy �� ��ȯ 
	const std::string getName() { return name; } // �̸� ���� 
};

class Oval : public Shape
{

public:
	Oval(const std::string n, int w, int h);
	double getArea();
};

Oval::Oval(const std::string n = "", int w = 0, int h = 0) : Shape(n, w, h)
{

}

double Oval::getArea()
{
	return 3.14*width*height;
}

class Rect :public Shape
{
public:
	Rect(const std::string n, int w, int h);
	double getArea();
};

Rect::Rect(const std::string n = "", int w = 0, int h = 0) : Shape(n, w, h)
{

}

double Rect::getArea()
{
	return width*height;
}

class Triangular :public Shape
{
public:
	Triangular(const std::string n, int w, int h);
	double getArea();
};

Triangular::Triangular(const std::string n = "", int w = 0, int h = 0) : Shape(n, w, h)
{

}

double Triangular::getArea()
{
	return width*height / 2;
}