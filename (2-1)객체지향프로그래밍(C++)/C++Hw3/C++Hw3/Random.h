#pragma once
#include <cstdlib>
#include <ctime>

class Random
{
public:
	Random();
	int next();
	int nexInRange(int start, int end);
};

Random::Random()
{
	srand((unsigned)time(0));
}

int Random::next()
{
	
	return rand();
}

int Random::nexInRange(int start, int end)
{
	

	return rand() % (end - start + 1) + start;
}