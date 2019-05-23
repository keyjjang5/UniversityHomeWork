#pragma once

class Map
{
	static const int xSize = 10;
	static const int ySize = 10;
	char field[ySize][xSize];
	int itemNum;


public:
	Map() : itemNum(xSize*ySize)
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
		printf("남은 아이템 수 : %d \n", itemNum);
	}

	bool existItem()
	{
		if (itemNum == 0)
			return false;
		return true;
	}
};