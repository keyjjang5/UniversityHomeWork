#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>

#include "Character.h"
#include "Bullet.h"
#include "Screen.h"

using namespace std;

int main()
{
	Character player("(^_^)", 30);
	Character enemy("(*_*)", 90);
	Screen screen;

	while (1)
	{
		//screen.clear();

		//ÀÔ·ÂºÎ
		if (_kbhit())
		{
			char key = _getch();
			printf("%d\n", key);
			if (key == 27)
				break;
			if (key == -32)
			{
				key = _getch();
				printf("%d\n", key);
			}

			switch (key)
			{
			case('a'): case(75):
				//player.decreasePos();
				break;

			case('d'): case(77):
				//player.increasePos();
				break;

			/*case(' '):
				bulletPos[bulletNum] = playerPos;
				bulletNum++;
				break;*/
			}
		}
		//screen.replace(player.returnPos(), player.returnShape().length()-1, player.returnShape());
		//screen.replace(enemy.returnPos(), enemy.returnShape().length()-1, enemy.returnShape());

		//screen.print();
	}
	return 0;
}