#pragma once

#include "Character.h"


class CharacterManager
{
	int listSize;
	Character* list;
	Map* map;
	int count;
	int moveCount;

public:
	CharacterManager(int listSize, Map* map) : listSize(listSize), map(map), count(0), moveCount(0)
	{
		list = (Character*)calloc(listSize, sizeof(Character));
	}

	void add(int x, int y, char shape)
	{
		list[count] = Character(x, y, shape, this->map);
		if (count != listSize)
			count++;
	}

	Character* getList()
	{
		return list;
	}

	int getCount()
	{
		return count;
	}

	int getListSize()
	{
		return listSize;
	}

	void update()
	{
		for (int i = 0; i < listSize; i++)
		{
			list[i].update();
		}
		moveCount++;
	}

	void print()
	{
		printf("ÀÌµ¿È½¼ö : %d\n", moveCount);
	}
};