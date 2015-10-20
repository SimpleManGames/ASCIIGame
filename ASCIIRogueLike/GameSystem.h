#pragma once
#include "Player.h"
#include "Level.h"
#include "GameState.h"
#include <string>
#include <iostream>

using namespace std;

class GameSystem
{
public:
	GameSystem(std::string levelFileName);
	void playGame();
	void exitGame();
	bool checkExit();
	void setWindow(int width, int height);

	void playerMove();
	void newPlayer();
	void savePlayer(std::string fileName);
	void loadPlayer(std::string fileName);
private:
	Level _level;
	Player _player;
};

