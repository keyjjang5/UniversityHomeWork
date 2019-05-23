#pragma once

#include <iostream>

class Date
{
	int year;
	int month;
	int day;

	char yymmdd[100];

public:
	Date(int year, int month, int day);
	Date(char* yymmdd);
	~Date();
	int getYear();
	int getMonth();
	int getDay();
	void show();
};

Date::Date(int year, int month, int day) : year(year), month(month), day(day)
{

}
Date::Date(char* yymmdd)
{
	char save[100];
	int count = 0;
	int saveCnt = 0;
	for (int i = 0; i <= strlen(yymmdd); i++)
	{
		if (yymmdd[i] == '/' || yymmdd[i] == NULL)
		{
			if (count == 0)
			{
				year = atoi(save);
				for (int j = 0; j < 100; j++)
					save[j] = NULL;
			}
			else if (count == 1)
			{
				month = atoi(save);
				for (int j = 0; j < 100; j++)
					save[j] = NULL;
			}
			else if (count == 2)
			{
				day = atoi(save);
				for (int j = 0; j < 100; j++)
					save[j] = NULL;

			}
			count++;
			saveCnt = 0;
			continue;
		}
		save[saveCnt] = yymmdd[i];
		saveCnt++;
	}
}
Date::~Date()
{

}

int Date::getYear()
{
	return year;
}
int Date::getMonth()
{
	return month;
}
int Date::getDay()
{
	return day;
}

void Date::show()
{
	std::cout << year << "³â" << month << "¿ù" << day << "ÀÏ" << std::endl;
}