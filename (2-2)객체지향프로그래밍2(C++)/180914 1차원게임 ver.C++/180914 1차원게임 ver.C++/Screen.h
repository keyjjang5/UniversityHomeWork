#pragma once
using namespace std;

class Screen
{
	const int length = 120;
	int frameLate = 100;
	std::string value;
	
public:
	Screen();
	void clear();
	void replace(int pos, size_t len,  std::string value);
	void print();
};

Screen::Screen()
{
	for (int i = 0;i < length;i++)
		value.append(" ");
}

void Screen::clear()
{
	value.clear();
	for (int i = 0; i < length; i++)
		value.append(" ");
}

void Screen::replace(int pos, size_t len, std::string value)
{
	this->value.replace(pos, len, value);
}

void Screen::print()
{
	value.erase(value.find_last_not_of(" \n\r\t") + 1);
	std::cout << value << '\r';

	Sleep(frameLate);
}