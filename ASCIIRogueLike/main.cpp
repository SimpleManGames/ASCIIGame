#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include "GameSystem.h"
#include "GameState.h"
#include "Player.h"

using namespace std;
std::string mapName = "level1.txt";

int main() {
	static int mapLevel = 1;
	GameState gameState(GameState::SPLASH);
	GameSystem gameSystem(mapName);
	gameSystem.setWindow(800, 600);
	while (gameState.currentState != GameState::EXIT) {
		switch (gameState.currentState) {
		case GameState::SPLASH:
			gameState.setTextFile(gameState.getSplashData(), "Splash.txt");
			gameState.drawTextFile(gameState.getSplashData());
			cin.get();
		case GameState::MENU:
			gameState.setTextFile(gameState.getMenuData(), "Menu.txt");
			gameState.drawTextFile(gameState.getMenuData());
			gameState.doMenuThings();
			break;
		case GameState::NEW:
			gameSystem.newPlayer();
			gameSystem.savePlayer("Player.txt");
			gameSystem.loadPlayer("Player.txt");
			gameState.currentState = GameState::PLAY;
			break;
		case GameState::LOAD:
			gameSystem.loadPlayer("Player.txt");
			break;
		case GameState::PLAY:
			gameSystem.playGame();
			break;
		case GameState::HOW:
			break;
		case GameState::EXIT:
			gameState.currentState = GameState::EXIT;
			break;
		}
	}

	return 0;
}