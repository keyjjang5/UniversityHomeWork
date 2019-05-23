#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "CharacterManager.h"
#include "Display.h"


int main()
{
	Map map;
	CharacterManager characterManager(4, &map);
	Display display(&characterManager, &map);

	characterManager.add(4, 4, 'A');
	characterManager.add(4, 6, 'B');
	characterManager.add(6, 4, 'C');
	characterManager.add(4, 6, 'E');

	map.clear();

	while (1)
	{
		display.clear();

		characterManager.update();

		map.update();

		display.update();

		// ȭ�� ���
		display.show();
		if (!map.existItem())
			break;
	}

	return 0;
}


0
*32//-+++/*
/*-4\
