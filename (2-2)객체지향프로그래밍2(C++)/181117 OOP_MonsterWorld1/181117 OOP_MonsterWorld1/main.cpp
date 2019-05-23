#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <conio.h>
#include "Enemies.h"
#include "Renderer.h"
#include "Map.h"


int main()
{
	Map map;
	Enemies enemies(map);
	
	enemies.add(Position(4, 4), "A");
	enemies.add(Position(4, 6), "B");
	enemies.add(Position(6, 4), "C");
	enemies.add(Position(6, 6), "E");

	clock_t current_tick, start_tick;

	start_tick = clock();
	
	map.clear();
	
	srand(time(NULL));

	while (true)
	{
		current_tick = clock();
		Renderer::getInstance().clear();

		enemies.update();
		map.update();

		map.draw();
		enemies.draw();

		Renderer::getInstance().render();
		Sleep(66 - (clock()- current_tick));

		if (!map.existItem())
			break;
	}

	Borland::gotoxy(0, 0);

	return 0;
}