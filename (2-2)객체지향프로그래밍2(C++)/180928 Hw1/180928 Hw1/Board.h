#pragma once

class Board
{
	int score;
	int level;
	int levelCount;
	int killCount;
	bool isPlay;

public:
	Board(int score, int level, int killCount);
	void update();
	void kill();

	bool onPlay();
	
	void setPlay(bool b);

	int getScore();
	int getLevel();
	int getKillCount();
};

Board::Board(int score = 0, int level = 1, int killCount = 0)
	: score(score), level(level), killCount(killCount), isPlay(true), levelCount(0)
{

}

void Board::update()
{
	if (levelCount >= 10)
	{
		level++;
		levelCount = 0;
	}
	score += level;
}

void Board::kill()
{
	killCount++;
	levelCount++;
}

bool Board::onPlay()
{
	return isPlay;
}

void Board::setPlay(bool b)
{
	isPlay = b;
}

int Board::getScore()
{
	return score;
}

int Board::getLevel()
{
	return level;
}

int Board::getKillCount()
{
	return killCount;
}