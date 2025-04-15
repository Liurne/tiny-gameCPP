#include "Map.hpp"

Map::Map() : _nbCollectible(0), _nbCollectibleLeft(0), _start((t_veci){.x = 0, .y = 0}), _enemy((t_veci){.x = 0, .y = 0}), _mapCreated(false) {
	std::cout << "Map constructor called, generating map" << std::endl;
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_map[i][j] = '0';
		}
	}
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
		_nbCollectible = rhs._nbCollectible;
		_nbCollectibleLeft = rhs._nbCollectibleLeft;
		_start = rhs._start;
		_enemy = rhs._enemy;
		_mapCreated = rhs._mapCreated;
	}
	return (*this);
}

void Map::generateMap() {
	_mapGenerator.getNewMap(_map);
	_parseMapElement();
	generateMapGrass();
	generateMapFlower();
	_mapCreated = true;
}

void Map::generateMapGrass() {
	GameLife gameLife(MAP_WIDTH, MAP_HEIGHT, MAP_GRASS_DENSITY);
	gameLife.generateGrid();
	gameLife.updateLife(15);
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_mapGrass[i][j] = gameLife.getCell(i, j);
		}
	}
}

void Map::generateMapGrass(float density) {
	GameLife gameLife(MAP_WIDTH, MAP_HEIGHT, density);
	gameLife.generateGrid();
	gameLife.updateLife(12);
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_mapGrass[i][j] = gameLife.getCell(i, j);
		}
	}
}

void Map::generateMapFlower() {
	GameLife gameLife(MAP_FLOWER_WIDTH, MAP_FLOWER_HEIGHT, MAP_FLOWER_RANDOM_DENSITY);
	gameLife.generateGrid();
	for (int32_t i = 0; i < MAP_FLOWER_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_FLOWER_HEIGHT; j++) {
			_mapRandomFlower[i][j] = gameLife.getCell(i, j);
		}
	}
	gameLife.generateGrid(MAP_FLOWER_WIDTH, MAP_FLOWER_HEIGHT, MAP_FLOWER_DENSITY);
	gameLife.updateLife(25);
	for (int32_t i = 0; i < MAP_FLOWER_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_FLOWER_HEIGHT; j++) {
			_mapFlower[i][j] = gameLife.getCell(i, j);
		}
	}
}

void Map::generateMapFlower(float density) {
	GameLife gameLife(MAP_FLOWER_WIDTH, MAP_FLOWER_HEIGHT, density);
	gameLife.generateGrid();
	for (int32_t i = 0; i < MAP_FLOWER_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_FLOWER_HEIGHT; j++) {
			_mapRandomFlower[i][j] = gameLife.getCell(i, j);
		}
	}
	gameLife.updateLife(25);
	for (int32_t i = 0; i < MAP_FLOWER_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_FLOWER_HEIGHT; j++) {
			_mapFlower[i][j] = gameLife.getCell(i, j);
		}
	}
}

char Map::getCell(int x, int y) const {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
		return '0';
	}
	return _map[x][y];
}

char Map::getCellGrass(int x, int y) const {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
		return '0';
	}
	return _mapGrass[x][y];
}

char Map::getCellFlower(int x, int y) const {
	if (x < 0 || x >= MAP_FLOWER_WIDTH || y < 0 || y >= MAP_FLOWER_HEIGHT) {
		return '0';
	}
	if (_mapRandomFlower[x][y] == '1' && _mapFlower[x][y] == '1') {
		return '1';
	}
	return '0';
}

void Map::_parseMapElement() {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			if (_map[i][j] == 'S') {
				_start.x = i;
				_start.y = j;
			}
			else if (_map[i][j] == 'E') {
				_enemy.x = i;
				_enemy.y = j;
			}
			else if (_map[i][j] == 'C') {
				_nbCollectible++;
			}
		}
	}
	_nbCollectibleLeft = _nbCollectible;
}

void displayMapImage(mlx_image_t *map_img, Map &map, t_mapDisplay *mapDisplay) {
	if (map_img->width != MAP_WIDTH * MAP_TILE_SIZE || map_img->height != MAP_HEIGHT * MAP_TILE_SIZE) {
		if (!resize_image(map_img, MAP_WIDTH * MAP_TILE_SIZE, MAP_HEIGHT * MAP_TILE_SIZE)) {
			exit_error("Failed to resize image");
		}
	}
	for (uint32_t i = 0; i < MAP_WIDTH; i++) {
		for (uint32_t j = 0; j < MAP_HEIGHT; j++) {
			char cell = map.getCell(i, j);
			if (cell == '0')
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, WATER_COLOR);
			else if (cell == '2')
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, BRIDGE_COLOR);
			else if (cell == 'C' && (mapDisplay->displayElement || mapDisplay->displayCollectible))
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, COLLECTIBLE_COLOR);
			else if (cell == 'S' && (mapDisplay->displayElement || mapDisplay->displaySpawn))
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, SPAWN_COLOR);
			else if (cell == 'E' && (mapDisplay->displayElement || mapDisplay->displayEnemy))
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, ENEMY_COLOR);
			else if (map.getCellGrass(i, j) == '1') 
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, LONG_GRASS_COLOR);
			else
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, SHORT_GRASS_COLOR);
		}
	}
	for (uint32_t i = 0; i < MAP_FLOWER_WIDTH; i++) {
		for (uint32_t j = 0; j < MAP_FLOWER_HEIGHT; j++) {
			if (map.getCellFlower(i, j) == '1' && map.getCell(i * 0.5, j * 0.5) == '1') {
				draw_rect(map_img, i * MAP_FLOWER_TILE_SIZE, j * MAP_FLOWER_TILE_SIZE, MAP_FLOWER_TILE_SIZE, MAP_FLOWER_TILE_SIZE, FLOWER_COLOR);
			}
		}
	}
	mlx_image_to_png(map_img, "map.png");
}

