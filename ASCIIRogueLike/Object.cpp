#include "Object.h"

Object::Object(std::string name, char tile, Type type) {
	_name = name;
	_tile = tile;
	_type = type;
}

void Object::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Object::getPosition(int x, int y) {
	x = _x;
	y = _y;
}

Object::Type Object::getType(Type type) {
	return _type;
}
