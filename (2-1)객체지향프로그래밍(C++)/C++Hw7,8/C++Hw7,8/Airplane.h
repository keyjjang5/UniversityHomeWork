#pragma once

class Airplane
{
	int time;
	std::string seat[8];
public:
	Airplane(int time);
	void reservation(int seat, std::string name);//예약
	void cancel(int seat, std::string name);
	void print();
	void setTime(int time);
	int getTime();
};

Airplane::Airplane(int time = 0) : time(time)
{
	for (int i = 0; i < 8; i++)
	{
		seat[i] = "---";
	}
}

void Airplane::reservation(int seat, std::string name)
{
	if (this->seat[seat] != "---")
		return;
	this->seat[seat] = name;
}

void Airplane::cancel(int seat, std::string name)
{
	if (this->seat[seat] == name)
		this->seat[seat] = "---";
}

void Airplane::setTime(int time)
{
	this->time = time;
}

int Airplane::getTime()
{
	return time;
}

void Airplane::print()
{
	for (int i = 0; i < 8; i++)
	{
		std::cout << "   " << seat[i];
	}
	std::cout << std::endl;
}

class Airport
{
	Airplane air[3];
public:
	Airport(int one, int two, int three);
	void reservationManage(int num, int seat, std::string name);
	void cancelManage(int num, int seat, std::string name);
	void printAll();
	void printAt(int pos);
};

Airport::Airport(int one, int two, int three)
{
	air[0].setTime(one);
	air[1].setTime(two);
	air[2].setTime(three);
}

void Airport::reservationManage(int num, int seat, std::string name)
{
	if (num >= 0 && num <= 3)
		air[num].reservation(seat, name);
}

void Airport::cancelManage(int num, int seat, std::string name)
{
	if (num >= 0 && num <= 3)
		air[num].cancel(seat, name);
}

void Airport::printAll()
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << air[i].getTime() << "시:";
		air[i].print();
	}
}

void Airport::printAt(int pos)
{
	std::cout << air[pos].getTime() << "시:";
	air[pos].print();
}