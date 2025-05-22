#include "Map.hpp"
# include "MapVisualGenerator.hpp"

Map::Map() : _nbCollectible(0), _nbCollectibleLeft(0), _start((t_veci){.x = 0, .y = 0}), _enemy((t_veci){.x = 0, .y = 0}), _mapCreated(false) {
	std::cout << "Map constructor called, generating map" << std::endl;
	_mapView = NULL;
	_mapPreview = NULL;
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_map[i][j] = '0';
		}
	}
}

Map::~Map() {
	if (_mapView) {
		mlx_delete_image(_mlx->getMlx(), _mapView);
	}
	if (_mapPreview) {
		mlx_delete_image(_mlx->getMlx(), _mapPreview);
	}
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

void Map::initView(MLXWrapper &mlx) {
	_mlx = &mlx;
	if (_mapView)
		return ;
	_mapView = mlx.newImage(MAP_WIDTH * TEXTURE_SIZE, MAP_HEIGHT * TEXTURE_SIZE);
	if (_mapPreview)
		return ;
	_mapPreview = mlx.newImage(MAP_WIDTH * MAP_TILE_SIZE, MAP_HEIGHT * MAP_TILE_SIZE);
	if (!_mapView || !_mapPreview) {
		exit_error(ERR_MLX_IMAGE);
	}
}

void Map::generateMap() {
	_mapGenerator.getNewMap(_map);
	_parseMapElement();
	generateMapDeep();
	generateMapGrass();
	generateMapFlower();
	if (_mapView) {
		MapVisualGenerator mapVisual;
		_mapView = mapVisual.generateMapImage(_mapView, *this);
		mlx_image_to_png(_mapView, "mapView.png");
	}
	displayMapPreview(_mapPreview, *this);
	mlx_image_to_png(_mapPreview, "mapPreview.png");
	_mapCreated = true;
}

void Map::generateMapDeep() {
	GameLife gameLife(MAP_WIDTH, MAP_HEIGHT, MAP_DEEP_DENSITY);
	gameLife.generateGrid();
	gameLife.updateLife(25);
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_mapDeep[i][j] = gameLife.getCell(i, j);
		}
	}
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

void Map::generateMapFlower() {
	GameLife gameLife(MAP_WIDTH, MAP_HEIGHT, MAP_RANDOM_DENSITY);
	gameLife.generateGrid();
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_mapRandom[i][j] = gameLife.getCell(i, j);
		}
	}
	gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_FLOWER_DENSITY);
	gameLife.updateLife(25);
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
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

char Map::getCellDeep(int x, int y) const {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
		return '0';
	}
	return _mapDeep[x][y];
}

char Map::getCellGrass(int x, int y) const {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
		return '0';
	}
	return _mapGrass[x][y];
}

char Map::getCellFlower(int x, int y) const {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
		return '0';
	}
	return _mapFlower[x][y];
}

char Map::getCellRandom(int x, int y) const {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
		return '0';
	}
	return _mapRandom[x][y];
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

void draw_map_cell(mlx_image_t *img, int x, int y, uint32_t color) {
	draw_rect(img, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, color);
}

void displayMapPreview(mlx_image_t *map_img, Map &map) {
	if (map_img->width < MAP_WIDTH * MAP_TILE_SIZE || map_img->height < MAP_HEIGHT * MAP_TILE_SIZE) {
		if (!resize_image(map_img, MAP_WIDTH * MAP_TILE_SIZE, MAP_HEIGHT * MAP_TILE_SIZE)) {
			exit_error("Failed to resize image");
		}
	}
	for (uint32_t i = 0; i < MAP_WIDTH; i++) {
		for (uint32_t j = 0; j < MAP_HEIGHT; j++) {
			if (map.getCell(i, j) == '0') {
				if (map.getCellDeep(i, j) == '1')
					draw_map_cell(map_img, i, j, WATER_COLOR);
				else
					draw_map_cell(map_img, i, j, DEEP_WATER_COLOR);
			}
			else if (map.getCell(i, j) == '3')
				draw_map_cell(map_img, i, j, WATER_COLOR);
			else if (map.getCell(i, j) == '1' || map.getCell(i, j) == 'C' || map.getCell(i, j) == 'S' || map.getCell(i, j) == 'E') {
				if (map.getCellGrass(i, j) == '1')
					draw_map_cell(map_img, i, j, LONG_GRASS_COLOR);
				else
					draw_map_cell(map_img, i, j, SHORT_GRASS_COLOR);
			}
			else if (map.getCell(i, j) == '2')
				draw_map_cell(map_img, i, j, BRIDGE_COLOR);
			else
				draw_map_cell(map_img, i, j, 0xFF0000FF);
		}
	}
	for (uint32_t i = 0; i < MAP_WIDTH; i++) {
		for (uint32_t j = 0; j < MAP_HEIGHT; j++) {
			if (map.getCell(i, j) == 'S') {
				draw_rect(map_img, (i * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.125, (j * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.125, MAP_TILE_SIZE * 0.75, MAP_TILE_SIZE * 0.75, SPAWN_COLOR);
			}
			else if (map.getCell(i, j) == 'E') {
				draw_rect(map_img, (i * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.125, (j * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.125, MAP_TILE_SIZE * 0.75, MAP_TILE_SIZE * 0.75, ENEMY_COLOR);
			}
			else if (map.getCell(i, j) == 'C') {
				draw_rect(map_img, (i * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.125, (j * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.125, MAP_TILE_SIZE * 0.75, MAP_TILE_SIZE * 0.75, COLLECTIBLE_COLOR);
			}
			if (map.getCellFlower(i, j) == '1' && (map.getCell(i, j) == '1' || map.getCell(i, j) == 'C')) {
				draw_rect(map_img, (i * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.25, (j * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.25, MAP_TILE_SIZE * 0.5, MAP_TILE_SIZE * 0.5, FLOWER_COLOR);
			}
			if (map.getCell(i, j) == '3' && map.getCellRandom(i, j) == '1') {
				draw_rect(map_img, (i * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.25, (j * MAP_TILE_SIZE) + MAP_TILE_SIZE * 0.25, MAP_TILE_SIZE * 0.5, MAP_TILE_SIZE * 0.5, LONG_GRASS_COLOR);
			}
		}
	}
}
