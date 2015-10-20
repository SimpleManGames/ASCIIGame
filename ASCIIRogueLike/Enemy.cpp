#include "Enemy.h"
#include <random>
#include <ctime>


Enemy::Enemy(std::string name, char tile, int level, int attack, int defense, int health, int xp) {
	_name = name;
	_tile = tile;
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_experienceValue = xp;
}

int Enemy::attack() {
	static std::default_random_engine randomEngine(time(NULL));

	std::uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

int Enemy::takeDamage(int attack) {
	attack -= _defense;
	if (attack > 0) {
		_health -= attack;

		if (_health <= 0) {
			return _experienceValue;
		}
	}
	return 0;
}

void Enemy::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Enemy::getPosition(int & x, int & y) {
	x = _x;
	y = _y;
}

std::string Enemy::getName() {
	return _name;
}

char Enemy::getMove(int playerX, int playerY) {
	static std::default_random_engine randEngine(time(NULL));
	std::uniform_int_distribution<int> moveRoll(0, 6);
	int distance;
	int dX = _x - playerX, 
		dY = _y - playerY;
	int adx = abs(dX),
		ady = abs(dY);

	distance = abs(_x - playerX) + abs(playerY - _y);

	if (distance <= 5) {
		// X axis
		if (adx > ady) {
			if (dX > 0) { return 'a'; }
			else { return 'd'; }
		}
		else { // Y axis
			if (dY > 0) { return 'w'; }
			else { return 's'; }
		}
	}

	int randMove = moveRoll(randEngine);
	switch (randMove) {
	case 0: return 'a';
	case 1: return 'w';
	case 2: return 's';
	case 3: return 'd';
	default: return '.';
	}
}
