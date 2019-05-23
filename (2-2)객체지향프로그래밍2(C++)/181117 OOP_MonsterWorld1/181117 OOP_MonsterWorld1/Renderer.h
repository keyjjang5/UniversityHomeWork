#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include "Utils.h"

using namespace std;

class Renderer {

	static const int xSize = 10;
	static const int ySize = 10;
	char		screen[ySize][xSize];
	Position	origin;

	Renderer() : origin(Borland::wherex(), Borland::wherey()) {
		// ���� ���� �������� �õ尪�� 10���� �����Ͽ� ������ ���� ���ڰ� �����ǵ��� ����.
		// ����� ����.
		// release�ÿ��� time(nullptr)�� �ٲپ� �õ尪�� ���������� �����ؾ� ��.
		srand(10);
	}

public:
	static Renderer& getInstance() {
		static Renderer instance;
		return instance;
	}	

	bool checkRange(const string& shape, Position pos)
	{
		int sz = shape.size();
		if (pos.x < 0) {
			if (pos.x + sz >= 0) return true;
		}
		else {
			if (pos.x + sz < xSize) return true;
		}
		return false;
	}

	bool checkRange(Position& pos)
	{
		if(pos.x >= 0 && pos.x < (xSize - 1))
			if(pos.y >= 0 && pos.y < (ySize - 1))
				return true;

		return false;
	}

	void clear()
	{
		for (int i = 0; i < xSize; i++)
		{
			for (int j = 0; j < ySize; j++)
			{
				screen[j][i] = ' ';
			}
		}
	}

	void draw(const string& shape, Position& pos)
	{
		string s = shape;
		s.erase(s.find_last_not_of(" \n\r\t") + 1);

		Position dest_pos = pos;
		if (checkRange(shape, pos) == false) return;

		const char* source = s.c_str();
		
		screen[pos.y][pos.x] = source[0];
	}

	void render()
	{
		// make sure it should end with proper ending characters.
		Borland::gotoxy(&origin);
		for (int i = 0; i < xSize; i++)
		{
			for (int j = 0; j < ySize; j++)
			{
				printf("%c", screen[j][i]);
			}
			printf("\n");
		}
		Borland::gotoxy(&origin);
	}

	////사용안함
	//int getScreenLength() { return screenSize; }
};

#endif 
