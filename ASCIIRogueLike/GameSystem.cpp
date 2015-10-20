#include "GameSystem.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

GameSystem::GameSystem(std::string levelFileName) {
	ifstream playerFile;
	playerFile.open("Player.txt");

	if (playerFile.fail()) {
		perror("Player.txt");
		system("pause");
		exit(1);
	}
	bool isEmpty;

	if (playerFile.is_open()) {
		playerFile.seekg(0, ios::end);
		size_t size = playerFile.tellg();
		if (size == 0) isEmpty = true;
		else isEmpty = false;
	}
	if (isEmpty = true) { newPlayer(); }
	else { loadPlayer("Player.txt"); }
	//_player.init(1, 100, 10, 10, 0);
	
	_level.load(levelFileName, _player);
}

void GameSystem::playGame() {
	bool isDone = false;
	
	while (isDone != true) {
		std::cout << string(100, '\n');
		std::cout << _player.getHP() << endl;
		_player.drawStats();
		_level.draw();
		playerMove();
		if (checkExit()) { savePlayer("Player.txt"); break; }
	}

}

void GameSystem::exitGame() {
	exit(1);
}
bool GameSystem::checkExit() {
	if (GetAsyncKeyState(VK_ESCAPE)) { return true; }
	return false;
}
void GameSystem::setWindow(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void GameSystem::newPlayer() {
	_player.setHP(_player.diceRoll(6, 6));
	_player.setMaxHP(_player.getHP());
	_player.setLvl(1);
	_player.setAtk(_player.diceRoll(6, 2));
	_player.setDef(_player.diceRoll(6, 3));
	_player.setXP(0);
	_player.addHPPot(1);
}

void GameSystem::savePlayer(string fileName) {
	ofstream file;

	file.open(fileName, ios::in);
	int tmp;

	if (file.fail()) {
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}

	tmp = _player.getLvl();
	file << tmp << endl;
	tmp = _player.getXP();
	file << tmp << endl;
	tmp = _player.getAtk();
	file << tmp << endl;
	tmp = _player.getDef();
	file << tmp << endl;
	tmp = _player.getHP();
}

void GameSystem::loadPlayer(std::string fileName) {
	std::ifstream file;
	file.open(fileName, ios::out);

	int tmp;
	int i = 0;
	string line;
	while (getline(file, line) && i < 5) {
		file >> tmp;
		switch (i) {
		case 0: _player.setLvl(tmp); break;
		case 1: _player.setXP(tmp); break;
		case 2: _player.setAtk(tmp); break;
		case 3: _player.setDef(tmp); break;
		case 4: _player.setHP(tmp); break;
		}
		i++;
	}
}

void GameSystem::playerMove() {
	char input;
	std::cout << "Enter a command (W/A/S/D)" << std::endl;
	input = _getch();

	_level.movePlayer(input, _player);
	_level.updateEnemies(_player);
}
