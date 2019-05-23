#pragma once

#include "Renderer.h"

class Map
{
	static const int xSize = 10;
	static const int ySize = 10;
	char field[ySize][xSize];
	int itemNum;
	Renderer& renderer;

public:
	Map() : itemNum(xSize*ySize), renderer(Renderer::getInstance())
	{
		// 초기화
		// x축
		for (int i = 0; i < xSize; i++)
		{
			// y축
			for (int j = 0; j < ySize; j++)
			{
				field[j][i] = ' ';
			}
		}
	}

	void update()
	{
		
	}

	void draw()
	{
		for (int i = 0; i < xSize; i++)
		{
			for (int j = 0; j < ySize; j++)
			{
				char c[2] = { getField(i, j) };
				string str = c;
				Position pos(i, j);
				renderer.draw(str, pos);
			}
		}

		Borland::gotoxy(12, 6);
		print();
	}

	void clear()
	{
		for (int i = 0; i < xSize; i++)
		{
			// y축
			for (int j = 0; j < ySize; j++)
			{
				field[j][i] = '0';
			}
		}
	}

	bool checkItem(int x, int y)
	{
		if (field[y][x] == '0')
			return true;

		return false;
	}

	void deleteItem(int x, int y)
	{
		field[y][x] = ' ';
		itemNum--;
	}

	char getField(int x, int y)
	{
		return field[y][x];
	}

	void print()
	{
		printf("# 남은 아이템 수 : %d \n", itemNum);
	}

	bool existItem()
	{
		if (itemNum == 0)
			return false;
		return true;
	}
};