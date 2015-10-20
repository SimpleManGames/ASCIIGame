#pragma once
#ifndef _FSTREAM_
#include <fstream>
#endif // !_FSTREAM_
#ifndef _IOSTREAM_
#include <iostream>
#endif // !_IOSTREAM_
#include <string>
#include <vector>

using namespace std;

class GameState
{
public:
	enum States { SPLASH, MENU, NEW, LOAD, PLAY, HOW, EXIT };
	GameState(States startState);
	States currentState;
	void changeState(States newState);

	vector <string> setTextFile(vector <string> &data, string fileName);
	vector<string> & getSplashData();
	vector<string> & getMenuData();

	vector<string>& getHowToData();

	int getNumValid(int min, int max);
	bool getValidKey(char key);

	void doMenuThings();

	void drawTextFile(vector<string> &data);
private:
	vector<string>_splashData;
	vector<string>_menuData;
	vector<string>_howToData;
};

