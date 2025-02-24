#include "Map.hpp"

Map::Map() : _width(MAP_WIDTH), _height(MAP_HEIGHT) {
	std::cout << "Map constructor called, generating map" << std::endl;
}

Map::~Map() {
	std::cout << "Map destructor called" << std::endl;
}

Map::Map(Map const &src) {
	std::cout << "Map copy constructor called" << std::endl;
	*this = src;
}

Map &Map::operator=(Map const &rhs) {
	std::cout << "Map assignment operator called" << std::endl;
	if (this != &rhs) {
		_width = rhs._width;
		_height = rhs._height;
	}
	return (*this);
}

int32_t Map::getWidth() const {
	return (_width);
}

int32_t Map::getHeight() const {
	return (_height);
}