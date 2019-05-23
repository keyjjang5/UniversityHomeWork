#pragma once

#include "CharacterManager.h"
#include <cstring>

class Display
{
	static const int xSize = 10;
	static const int ySize = 10;

	char screen[ySize][xSize];

	CharacterManager* characterManager;
	Map* map;


public:
	Display(CharacterManager* manager, Map* map) : characterManager(manager), map(map)
	{
		// 초기화
		// x축
		for (int i = 0; i < xSize; i++)
		{
			// y축
			for (int j = 0; j < ySize; j++)
			{
				screen[j][i] = ' ';
			}
		}
	}

	void update()
	{
		// map draw
		for (int i = 0; i < xSize; i++)
		{
			for (int j = 0; j < ySize; j++)
			{
				screen[j][i] = map->getField(i, j);
			}
		}

		// character draw
		Character* list = characterManager->getList();
		int count = characterManager->getCount();
		
		for (int i = 0; i < characterManager->getCount(); i++)
		{

			int x = list[i].getX();
			int y = list[i].getY();
			screen[y][x] = list[i].getShape();
		}
	}
	// 실제 사용은 안함
	void draw(Map* p)
	{
		for (int i = 0; i < xSize; i++)
		{
			for (int j = 0; j < ySize; j++)
			{
				screen[j][i] = map->getField(i, j);
			}
		}
	}
	// 실제 사용은 안함
	void draw(CharacterManager* manager)
	{
		Character* list = characterManager->getList();

		for (int i = 0; i < characterManager->getCount(); i++)
		{
			
			int x = list[i].getX();
			int y = list[i].getY();
			screen[y][x] = list[i].getShape();
		}
	}
	// 초기화
	void clear()
	{
		// 초기화
		// x축
		for (int i = 0; i < xSize; i++)
		{
			// y축
			for (int j = 0; j < ySize; j++)
			{
				screen[j][i] = ' ';
			}
		}
	}

	void show()
	{
		system("cls");
		// x축
		for (int i = 0; i < xSize; i++)
		{
			// y축
			for (int j = 0; j < ySize; j++)
			{
				printf("%c", screen[j][i]);
			}
			printf("\n");
		}
		
		printf("\n\n");
		characterManager->print();
		map->print();

		Character* list = characterManager->getList();
		for (int i = 0; i < characterManager->getListSize(); i++)
		{
			list[i].print();
		}

		_sleep(100);
	}
};