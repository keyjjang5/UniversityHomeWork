#pragma once

#include <iostream>

class Oval
{
	int width;
	int height;

public:
	Oval(int width, int height);
	~Oval();
	int getWidth();
	int getHeight();
	void set(int w, int h);
	void show();
};

Oval::Oval(int width = 0, int height = 0) : width(width), height(height)
{
	
}


Oval::~Oval()
{
	std::cout << "Oval¼Ò¸ê : " << width << ' ' << height << std::endl;
}

int Oval::getWidth()
{
	return width;
}

int Oval::getHeight()
{
	return height;
}

void Oval::set(int w, int h)
{
	width = w;
	height = h;
}

void Oval::show()
{
	std::cout << "width : " << width << " height : " << height << std::endl;
}