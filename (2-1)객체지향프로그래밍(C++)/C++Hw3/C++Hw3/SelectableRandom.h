#pragma once

#include <cstdlib>
#include <ctime>

class SelectableRandom
{
	int n;
public:
	SelectableRandom(int n);
	int next();
	int nexInRange(int start, int end);
};

SelectableRandom::SelectableRandom(int n) : n(n)
{
	srand((unsigned)time(0));
}

int SelectableRandom::next()
{
	int r = rand();
	if(n%2 == 0)
	{
		if (r % 2 == 0)
			return r;
		else
			return r + 1;
	}
	else if (n % 2 == 1)
	{
		if (r % 2 == 0)
			return r + 1;
		else
			return r;
	}
	
}

int SelectableRandom::nexInRange(int start, int end)
{
	int r = rand() % (end - start + 1) + start;

	if (n % 2 == 0)
	{
		if (r % 2 == 0)
			return r;
		else
			return nexInRange(start, end);
	}
	else if (n % 2 == 1)
	{
		if (r % 2 == 0)
			return nexInRange(start, end);
		else
			return r;
	}
}