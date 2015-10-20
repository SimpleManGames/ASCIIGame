#include "GameState.h"

GameState::GameState(GameState::States startState) {
}

void GameState::changeState(States newState) {
	currentState = newState;
}

bool is_textfile_empty(const char* filename)
{
	string   s;
	ifstream f(filename, ios::binary);

	// Check for UTF-8 BOM
	if (f.peek() == 0xEF)
	{
		f.get();
		if (f.get() != 0xBB) return false;
		if (f.get() != 0xBF) return false;
	}

	// Scan every line of the file for non-whitespace characters
	while (getline(f, s))
	{
		if (s.find_first_not_of(
			" \t\n\v\f\r" // whitespace
			"\0\xFE\xFF"  // non-printing (used in various Unicode encodings)
			) != string::npos)
			return false;
	}

	// If we get this far, then the file only contains whitespace
	// (or its size is zero)
	return true;
}
vector <string> GameState::setTextFile(vector <string> &data, string fileName) {
	ifstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}
	string line;
	while (getline(file, line)) {
		data.push_back(line);
	}
	file.close();
	return data;
}

vector<string> & GameState::getSplashData() { return _splashData; }
vector<string> & GameState::getMenuData() { return _menuData; }

int  GameState::getNumValid(int min, int max)
{
	int select;

	do
	{
		std::cout << "Enter a valid number (" << min << "-" << max << "): ";
		std::cin >> select;

		if (std::cin.fail() || select < min || select > max)
		{
			std::cin.clear();			//clears the input buffer
			std::cin.ignore(80, '\n');	//resets the input buffer
			std::cout << "Invalid entry." << std::endl;
		}
		else break; //stop looping if the input was valid
	} while (true);

	return select;
}
bool GameState::getValidKey(char key)
{
	char tmp;
	bool match = true;
	do {
		std::cin >> tmp;

		if (std::cin.fail() || tmp != key)
		{
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cout << "Sorry what was that?" << std::endl;
		}
		else break;
	} while (true);

	return match;
}

void GameState::doMenuThings() {
	switch (getNumValid(1, 4)) {
	case 1: GameState::currentState = GameState::PLAY; break;
	case 2: GameState::currentState = GameState::NEW; break;
	case 3: GameState::currentState = GameState::HOW; break;
	case 4: GameState::currentState = GameState::EXIT; break;
	}
}

void GameState::drawTextFile(vector<string> &data) {
	system("cls");
	for (int i = 0; i < data.size(); i++) {
		printf("%s\n", data[i].c_str());
	}
}
