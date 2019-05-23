#pragma once

#include <iostream>

class Integer
{
	int i;

public:
	Integer(int getI) : i(getI)
	{

	}
	Integer(char* getS) : i(atoi(getS))
	{

	}
	void set(int setI)
	{
		i = setI;
	}

	int get()
	{
		return i;
	}

	bool isEven()
	{
		if (i % 2 == 0)
			return true;
		else if (i % 2 == 1)
			return false;
	}
};