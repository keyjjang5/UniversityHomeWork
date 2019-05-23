#pragma once

class Screen
{
	const int length = 119;
	char value[119 + 1 + 1];
	int frameLate;
	bool isEnd;

public:
	Screen(int frameLate);
	void draw(int pos, size_t len, char* value);
	void print();
	void clear();
};

Screen::Screen(int frameLate = 100)
	: frameLate(frameLate), isEnd(false)
{
	memset(value, ' ', length);
}

void Screen::draw(int pos, size_t len, char* value)
{
	if (pos < 0)
		return;
	strncpy(this->value + pos, value, len);
}

void Screen::print()
{
	value[length] = '\r';
	value[length + 1] = 0;
	printf("%s", value);

	memset(value, ' ', length);

	_sleep(frameLate);
}

void Screen::clear()
{
	memset(value, ' ', length);
}