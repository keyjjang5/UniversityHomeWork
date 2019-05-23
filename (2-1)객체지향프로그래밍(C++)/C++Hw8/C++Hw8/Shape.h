#pragma once

class Shape
{
protected:
	std::string name; // 도형의 이름 
	int width, height; // 도형이 내접하는 사각형의 너비와 높이 

public:
	Shape(const std::string n = "", int w = 0, int h = 0) : name(n), width(w), height(h) {}
	virtual double getArea() { return 0; } // dummy 값 반환 
	const std::string getName() { return name; } // 이름 리턴 
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