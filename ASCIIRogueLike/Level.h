#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Object.h"

using namespace std;

class Level
{
public:
	Level();

	void load(string fileName, Player &player);
	void draw();

	void movePlayer(char input, Player &player);
	void updateEnemies(Player &player);
	char getTile(int x, int y);
	void setTile(int x, int y, char tile);

private:
	vector <string> _levelData;
	vector <Enemy> _enemies;
	vector <Object> _object;

	void processPlayerMove(Player &player, int targetX, int targetY);
	void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
	void battleMonster(Player &player, int targetX, int targetY);
	void useObject(Player & player, int targetX, int targetY);
};

