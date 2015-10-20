#pragma once
#include <fstream>
class Player
{
public:
	enum Stats { LEVEL, HEALTH, ATTACK, DEFENSE, EXPERIENCE };

	Player();
	void init(int level, int health, int attack, int defense, int experience);

	int attack();

	void addExperience(int experience);
	int takeDamage(int attack);
	
	#pragma region Gets/Sets
	void setPosition(int x, int y);
	void getPosition(int &x, int &y);

	int & getAtk();
	void setAtk(int value);
	int & getLvl();
	void setLvl(int value);
	int & getHP();
	void setHP(int value);
	int & getMaxHP();
	void setMaxHP(int value);
	int & getDef();
	void setDef(int value);
	int & getXP();
	void setXP(int value);

	int & getGold();
	void setGold(int value);
	void addGold(int value);

	int & getHPPot();
	void addHPPot(int value);
	void useHPPot();
#pragma endregion

	int diceRoll(int sides, int qty);
	void drawStats();

	void processNewWeapon(int newDamage);
	void processNewArmor(int newArmor);

	~Player();
	bool getValidKey(char key);
private:
	int _level;
	int _health;
	int _maxHealth;
	int _attack;
	int _defense;
	int _experience;

	int _gold;
	int _hpPot;

	int _weaponMod;
	int _currentWeapMod;
	int _armorMod;
	int _currentArmMod;

	int _x;
	int _y;
};

