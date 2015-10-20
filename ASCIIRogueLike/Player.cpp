#include "Player.h"
#include <random>
#include <ctime>
#include <iostream>
#include <string>


Player::Player() {
	_x = 0;
	_y = 0;
}

void Player::init(int level, int health, int attack, int defense, int experience) {
	_level = level;
	_attack = attack;
	_health = health;
	_maxHealth = health;
	_defense = defense;
	_experience = experience;

	_gold = 0;
	_hpPot = 1;

	_weaponMod = 0;
	_armorMod = 0;
}

int Player::attack() {
	static std::default_random_engine randomEngine(time(NULL));

	std::uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

void Player::addExperience(int experience) {
	_experience += experience;

	while (_experience > 50) {
		std::cout << "Level up!" << std::endl;
		_experience -= 50;
		_attack += 10;
		_attack += 5;
		_health += 15;
		_maxHealth += 15;
		_defense += 5;
		_level++;
		system("PAUSE"); 
	}
}

int Player::takeDamage(int attack) {
	attack -= _defense;
	if (attack > 0) {
		_health -= attack;

		if (_health <= 0) {
			return 1;
		}
	}
	else {
		return attack;
	}
}

void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}
void Player::getPosition(int & x, int & y) {
	x = _x;
	y = _y;
}

int & Player::getAtk() { return _attack; }
void Player::setAtk(int value) { _attack = value; }

int & Player::getLvl() { return _level; }
void Player::setLvl(int value) { _level = value; }

int & Player::getHP() { return _health; }
void Player::setHP(int value) { _health = value; }

int & Player::getMaxHP() {
	return _maxHealth;
}

void Player::setMaxHP(int value) {
	_maxHealth = value;
}

int & Player::getDef() { return _defense; }
void Player::setDef(int value) { _defense = value; }

int & Player::getXP() { return _experience; }
void Player::setXP(int value) { _experience = value; }

int & Player::getGold() {
	return _gold;
}

void Player::setGold(int value) {
	_gold = value;
}

void Player::addGold(int value) {
	_gold += value;
}

int & Player::getHPPot() {
	return _hpPot;
}

void Player::addHPPot(int value) {
	_hpPot += value;
}

void Player::useHPPot() {
	if (_hpPot > 0) {
		_hpPot--;
		_health = _maxHealth;
	}
}

int  Player::diceRoll(int sides, int qty) {
	srand(time(NULL));
	int r_roll = 0;

	for (int i = 0; i < qty; ++i) {
		r_roll += rand() % sides + 1;
	}
	return r_roll;
}

void Player::drawStats() {
	std::cout << "Level: " << _level << std::endl;
	std::cout << "Experience: " << _experience << std::endl;
	std::cout << "Health: " << _health << " / " << _maxHealth << std::endl;
	std::cout << "Attack: " << _attack << std::endl;
	std::cout << "Defense: " << _defense << std::endl;
	std::cout << "HP Potions " << _hpPot << std::endl;
	std::cout << "Gold " << _gold << std::endl;
}

void Player::processNewWeapon(int newDamage) {
	std::cout << "You found a new weapon of " << newDamage << std::endl;
	std::cout << "Your old one does" << _currentWeapMod << std::endl;
	std::cout << "Do you want to switch weapons?" << std::endl;
	if (getValidKey('y') || getValidKey('Y')) {
		_currentWeapMod = newDamage; }
	else _currentWeapMod = _currentWeapMod;
}
void Player::processNewArmor(int newArmor) {
	std::cout << "You found a new armor of " << newArmor << std::endl;
	std::cout << "Your old one does" << _currentArmMod << std::endl;
	std::cout << "Do you want to switch amor?" << std::endl;
	if (getValidKey('y') || getValidKey('Y')) {
		_currentArmMod = newArmor;
	}
	else _currentArmMod = _currentArmMod;
}

Player::~Player() {

}

bool Player::getValidKey(char key)
{
	char tmp;
	bool match = true;
	do {
		std::cin >> tmp;

		if (std::cin.fail() || tmp != key)
		{
			std::cin.clear();
			std::cin.ignore(80, '\n');
		}
		else break;
	} while (true);

	return match;
}