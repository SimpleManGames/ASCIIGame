#pragma once
#include <string>

class Object
{
public:
	enum Type { CHEST, DOOR, LADDERUP, LADDERDOWN, DNU };
	Object(std::string name, char tile, Type type);

	void setPosition(int x, int y);
	void getPosition(int x, int y);

	Type getType(Type type);
private:
	std::string _name;
	char _tile;
	Type _type;

	int _x;
	int _y;


};