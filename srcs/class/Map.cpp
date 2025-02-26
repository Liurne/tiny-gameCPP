#include "Map.hpp"

Map::Map(){
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
		for (int32_t i = 0; i < MAP_WIDTH; i++) {
			for (int32_t j = 0; j < MAP_HEIGHT; j++) {
				_map[i][j] = rhs._map[i][j];
			}
		}
	}
	return (*this);
}

void Map::generateMap() {
	GameLife gameLife;
	gameLife.generateGrid();
	for (int i = 0; i < 10; i++) {
		gameLife.updateLife();
	}
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_map[i][j] = gameLife.getGrid()[i][j];
		}
	}
}

void Map::displayMap(mlx_image_t *renderer) const {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			if (_map[i][j] == '1') {
				fill_img(renderer, 0x00FF00FF);
			}
			else if (_map[i][j] == 'S') {
				fill_img(renderer, 0x00FFFFFF);
			}
			else if (_map[i][j] == 'E') {
				fill_img(renderer, 0xFF00FFFF);
			}
			else if (_map[i][j] == 'C') {
				fill_img(renderer, 0xFFFF00FF);
			}
			else {
				fill_img(renderer, 0x0000FFFF);
			}
		}
	}
}

void Map::_placeMapStart() {
	int side = rand() % 4;
	int x;
	if (side % 2)
		x = rand() % (MAP_WIDTH - MAP_MARGING * 2) + MAP_MARGING;
	else
		x = rand() % (MAP_HEIGHT - MAP_MARGING * 2) + MAP_MARGING;
}

void Map::_placeMapExit() {

}

void Map::_placeMapElement() {

}


void Map::_verifyMapElement() {
}

void Map::_clearWrongMapElement() {
}

