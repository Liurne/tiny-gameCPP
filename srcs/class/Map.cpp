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
	uint32_t width = (rand() % (int)(MAP_WIDTH - MAP_WIDTH_MIN)) + MAP_WIDTH_MIN;
	uint32_t height = (rand() % (int)(MAP_HEIGHT - MAP_HEIGHT_MIN)) + MAP_HEIGHT_MIN;
	// width = 30;
	// height = 30;
	std::cout << "Map generated (Size: " << width << ", " << height << ")" << std::endl;
	_mapGenerator.generateMap(_map, width, height, MAP_DENSITY);
	// _mapGenerator.generateMap(_map);
	_parseMapElement();
	generateMapGrass();
	generateMapGrassBig();
	_mapCreated = true;
}

void Map::generateMap(float density) {
	std::cout << "Generating map with density: " << density << std::endl;
	uint32_t width = (rand() % (int)(MAP_WIDTH - MAP_WIDTH_MIN)) + MAP_WIDTH_MIN;
	uint32_t height = (rand() % (int)(MAP_HEIGHT - MAP_HEIGHT_MIN)) + MAP_HEIGHT_MIN;
	std::cout << "Map generated (Size: " << width << ", " << height << ")" << std::endl;
	_mapGenerator.generateMap(_map, width, height, density);
	_parseMapElement();
	generateMapGrass();
	generateMapGrassBig();
	_mapCreated = true;
}

void Map::generateMapElement() {
	_mapGenerator.generateMapElement(_map);
	_parseMapElement();
}

void Map::generateCollectible() {
	_mapGenerator.generateCollectible(_map);
	_parseMapElement();
}

void Map::genrateStart() {
	_mapGenerator.generateStart(_map);
	_parseMapElement();
}

void Map::generateEnemy() {
	_mapGenerator.generateEnemy(_map);
	_parseMapElement();
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

void Map::generateMapGrassBig() {
	GameLife gameLife(MAP_FLOWER_WIDTH, MAP_FLOWER_HEIGHT, MAP_GRASS_DENSITY);
	gameLife.generateGrid();
	gameLife.updateLife(50);
	for (int32_t i = 0; i < MAP_FLOWER_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_FLOWER_HEIGHT; j++) {
			_mapFlower[i][j] = gameLife.getCell(i, j);
		}
	}
}

void Map::generateMapGrassBig(float density) {
	GameLife gameLife(MAP_FLOWER_WIDTH, MAP_FLOWER_HEIGHT, density);
	gameLife.generateGrid();
	gameLife.updateLife(50);
	for (int32_t i = 0; i < MAP_FLOWER_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_FLOWER_HEIGHT; j++) {
			_mapFlower[i][j] = gameLife.getCell(i, j);
		}
	}
}

void Map::setNbCollectible(uint32_t nbCollectible) {
	_nbCollectible = nbCollectible;
	_mapGenerator.generateCollectible(_map, nbCollectible);
	_parseMapElement();
}

char Map::getCell(int x, int y) {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
		return '0';
	}
	return _map[x][y];
}

char Map::getCellGrass(int x, int y) {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
		return '0';
	}
	return _mapGrass[x][y];
}

char Map::getCellGrassBig(int x, int y) {
	if (x < 0 || x >= MAP_FLOWER_WIDTH || y < 0 || y >= MAP_FLOWER_HEIGHT) {
		return '0';
	}
	return _mapFlower[x][y];
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
			if (cell == '0') {
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, WATER_COLOR);
			}
			else if (cell == 'C' && (mapDisplay->displayElement || mapDisplay->displayCollectible)){
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, COLLECTIBLE_COLOR);
			}
			else if (cell == 'S' && (mapDisplay->displayElement || mapDisplay->displaySpawn)){
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, SPAWN_COLOR);
			}
			else if (cell == 'E' && (mapDisplay->displayElement || mapDisplay->displayEnemy)){
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, ENEMY_COLOR);
			}
			else if (map.getCellGrass(i, j) == '1') {
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, LONG_GRASS_COLOR);
			}
			else {
				draw_rect(map_img, i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, SHORT_GRASS_COLOR);
			}
		}
	}
	mlx_image_to_png(map_img, "map.png");
}

