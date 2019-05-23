#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Map.h"


class Character
{
	char shape;
	int x;
	int y;
	int itemCount;
	Map* map;

public:
	Character(int x, int y, char shape, Map* map) : x(x), y(y), shape(shape), itemCount(0), map(map)
	{
		
	}
	
	void update()
	{
		// 이동
		move();
		// 아이템이 있는지 확인하고 있으면 먹음
		checkItem();
	}

	void move()
	{
		int randx = rand() % 3 - 1;
		int randy = rand() % 3 - 1;
		
		randx = rand() % 3 - 1;
		randy = rand() % 3 - 1;

		x += randx;
		
		y += randy;
		
		if (x > 9)
			x = 9;
		if (x < 0)
			x = 0;

		if (y > 9)
			y = 9;
		if (y < 0)
			y = 0;
	}

	void checkItem()
	{
		if (map->checkItem(x, y))
		{
			map->deleteItem(x, y);
			itemCount++;
		}
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	char getShape()
	{
		return shape;
	}

	void print()
	{
		printf("%c : %d\n", shape, itemCount);
	}
};