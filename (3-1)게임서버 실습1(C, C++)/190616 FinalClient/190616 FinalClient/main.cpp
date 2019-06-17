#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <conio.h>

#include "Renderer.h"
#include "Logs.h"

int main()
{
	string name = "Alchemy";
	Logs playerLog(name, 5, 0, 0);
	Logs enemyLog(name, 5, 70, 0);

	Message message;

	clock_t current_tick, start_tick;

	start_tick = clock();
	while (true)
	{
		current_tick = clock();
		Renderer::getInstance().clear();

		if (_kbhit()) {
			char key = _getch();
			//printf("%d\n", key);
			if (key == 27) break;
			if (key == -32) {
				key = _getch();
			}

			switch (key) {
			case 'q':
				playerLog.WriteLog(Message::attack);
				break;
			case 'w':
				playerLog.WriteLog(Message::doubleAttack);
				break;
			case 'e':
				playerLog.WriteLog(Message::defend);
				break;
			case 'r':
				playerLog.WriteLog(Message::doubleDefend);
				break;
			case ' ':
				playerLog.WriteLog(Message::charge);
				break;
			}
		}
		/*enemies.update();
		bullets.update();
		players.update();*/
		//main = players.getMainCharacter();
		if (main == nullptr) break;

		//enemies.draw();
		//bullets.draw();
		//players.draw();
		


		playerLog.Update();
		//enemyLog.Update();

		//Renderer::getInstance().render();
		Sleep(50 - (clock() - current_tick));
	}
	system("cls");


	return 0;
}