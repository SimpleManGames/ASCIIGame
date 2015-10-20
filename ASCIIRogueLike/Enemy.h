#pragma once
#include <string>
class Enemy
{
public:
	Enemy(std::string name, char tile, int level, int attack, int defense, int health, int xp);

	int attack();
	int takeDamage(int attack);

	void setPosition(int x, int y);
	void getPosition(int &x, int &y);

	std::string getName();
	char getTile() { return _tile; }

	char getMove(int playerX, int playerY);
private:
	std::string _name;
	char _tile;

	int _level;
	int _health;
	int _defense;
	int _attack;
	int _experienceValue;

	int _x, _y;
};

