#include "Level.h"
#include <fstream>
#include <iostream>

Level::Level() {

}

void Level::load(string fileName, Player &player) {
	ifstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}
	string line;

	while (getline(file, line)) {
		_levelData.push_back(line);
	}
	file.close();

	//Process level
	char tile;
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@':
				player.setPosition(j, i);
				break;
			case 's': // Snake
				_enemies.push_back(Enemy("Snake", tile, 1, player.diceRoll(3, 1), 1, 10, 15));
				_enemies.back().setPosition(j, i);
				break;
			case 'g': // Goblin
				_enemies.push_back(Enemy("Goblin", tile, 2, player.diceRoll(5, 1), 5, 25, 20));
				_enemies.back().setPosition(j, i);
				break;
			case 'b': // Bandit
				_enemies.push_back(Enemy("Bandit", tile, 3, player.diceRoll(7, 1), 6, 30, 30));
				_enemies.back().setPosition(j, i);
				break;
			case 'o': // Ogre
				_enemies.push_back(Enemy("Ogre", tile, 4, player.diceRoll(15, 1), 10, 45, 50));
				_enemies.back().setPosition(j, i);
				break;
			case 'D': // Dragon
				_enemies.push_back(Enemy("Dragon", tile, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX));
				_enemies.back().setPosition(j, i);
				break;
			case 'c': // Chest
				_object.push_back(Object("Chest", tile, Object::CHEST));
				_object.back().setPosition(j, i);
				break;
			}
		}
	}
}

void Level::draw() {
	for (int i = 0; i < _levelData.size(); i++) {
		printf("%s\n", _levelData[i].c_str());
	}
}

void Level::movePlayer(char input, Player &player) {
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);
	
	char moveTile;

	switch (input) {
	case 'W': case 'w': processPlayerMove(player, playerX, playerY - 1); break;
	case 'S': case 's': processPlayerMove(player, playerX, playerY + 1); break;
	case 'A': case 'a': processPlayerMove(player, playerX - 1, playerY); break;
	case 'D': case 'd': processPlayerMove(player, playerX + 1, playerY); break;
	case 'H': case 'h': player.useHPPot();
	default: break;
	}
}

void Level::updateEnemies(Player & player) {
	char aiMove;
	int playerX, playerY;
	int enemyX, enemyY;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);
		switch (aiMove) {
		case 'w': processEnemyMove(player, i, enemyX, enemyY - 1); break;
		case 's': processEnemyMove(player, i, enemyX, enemyY + 1); break;
		case 'a': processEnemyMove(player, i, enemyX - 1, enemyY); break;
		case 'd': processEnemyMove(player, i, enemyX + 1, enemyY); break;
		}
	}
}

char Level::getTile(int x, int y) {
	return  _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;
}

void Level::processPlayerMove(Player & player, int targetX, int targetY) {
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);
	switch (moveTile) {
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	case 'c':
		useObject(player, targetX, targetY);
		break;
	default:
		battleMonster(player, targetX, targetY);
		break;
	}
}

void Level::processEnemyMove(Player & player, int enemyIndex, int targetX, int targetY) {
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;
	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);
	switch (moveTile) {
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '#':
		break;
	case '@':
		battleMonster(player, enemyX, enemyY);
	default:
		break;
	}
}

void Level::battleMonster(Player & player, int targetX, int targetY) {
	int enemyX, enemyY;
	int playerX, playerY;
	int attackRoll;
	int attackResult;

	player.getPosition(playerX, playerY);
	
	for (int i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPosition(enemyX, enemyY);
		//Player attack
		if (targetX == enemyX && targetY == enemyY) {
			attackRoll = player.attack();
			std::cout << "Player attack monster for " << attackRoll << "before mitigation!" << std::endl;
			//printf("Player attack %s for %d\n", _enemies[i].getName(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);
			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				std::cout << string(100, '\n');
				draw();
				player.addExperience(attackResult);
				std::cout << _enemies[i].getName() << " died!" << endl;

				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;

				return;
			}
			// Monster attack
			attackRoll = _enemies[i].attack();
			std::cout << _enemies[i].getName() << " attack for " << attackRoll << "before mitigation!"<< std::endl;
			//printf("%s attack for %d\n", _enemies[i].getName(), attackRoll);
			attackResult = player.takeDamage(attackRoll);
			if (attackResult > 0) { 
				player.setHP(player.getHP() - attackResult); 
			}
			if (player.getHP() <= 0) {
				std::cout << string(100, '\n');
				setTile(playerX, playerY, 'x');
				draw();
				std::cout << "You died!" << endl;
				system("PAUSE");
				ofstream file;
				file.open("Player.txt");
				file.close();
				exit(0);
			}
			system("PAUSE");
			return; 
		}
	}
}
void Level::useObject(Player &player, int targetX, int targetY) {
	int objectX = 0, objectY = 0;
	int playerX, playerY;
	Object::Type type = Object::DNU;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _object.size(); i++) {
		_object[i].getPosition(objectX, objectY);
		//if (targetX == objectX && targetY == objectY) {
			switch (_object[i].getType(type)) {
			case Object::CHEST:
				switch (player.diceRoll(10, 1)) {
				case 1:
				case 2: // Weapon
					static int weaponIncrease;
					weaponIncrease += 2;
					player.processNewWeapon(player.diceRoll(weaponIncrease, 1));
					break;
				case 3:
				case 4: // Armor
					static int armorIncrease;
					armorIncrease += 3;
					player.processNewArmor(player.diceRoll(armorIncrease, 1));
					break;
				case 5:
				case 6:
				case 7: // Potion
					player.addHPPot(player.diceRoll(3, 1));
					break;
				case 8:
				case 9:
				case 10: // Gold
					player.addGold(player.diceRoll(100, 1));
					break;
				}
				break;
			}
			setTile(targetX, targetY, '.');
		//}
	}
}
