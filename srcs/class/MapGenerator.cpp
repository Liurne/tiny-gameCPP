#include "MapGenerator.hpp"

//Constructor

MapGenerator::MapGenerator() {
	std::cout << "MapGenerator constructor called" << std::endl;
}

MapGenerator::~MapGenerator() {
	std::cout << "MapGenerator destructor called" << std::endl;
}

//Public

void	MapGenerator::generateMap(char newMap[MAP_WIDTH][MAP_HEIGHT]) {
	GameLife gameLife;
	gameLife.generateGrid();
	gameLife.updateLife(12);

	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_map[i][j] = gameLife.getCell(i, j);
			_mapping[i][j] = 0;
		}
	}
	_nbCollectibleMax = NB_MAX_COLLECTIBLE(MAP_WIDTH, MAP_HEIGHT);
	_nbCollectibleMin = NB_MIN_COLLECTIBLE(MAP_WIDTH, MAP_HEIGHT);

	_findIsland();
	std::cout << "Number of island: " << _nbIsland << std::endl;
	_placeMapStart();
	_placeMapEnemy();
	_placeMapCollectible();
	_verifyMapElement();
	_copyMap(newMap);
}

void	MapGenerator::generateMap(char newMap[MAP_WIDTH][MAP_HEIGHT], uint32_t width, uint32_t height,  float density) {
	if ( width < MAP_WIDTH_MIN || width > MAP_WIDTH || height < MAP_HEIGHT_MIN || height > MAP_HEIGHT) {
		std::cout << "Map size is not valid" << std::endl;
		return ;
	}
	_clearMap();
	GameLife gameLife(width, height, density);
	gameLife.generateGrid();
	gameLife.updateLife(15);
	uint32_t nbGroundTile = 0;
	for (int32_t i = MAP_WIDTH * 0.5 - width * 0.5; i < MAP_WIDTH * 0.5 + width * 0.5; i++) {
		for (int32_t j = MAP_HEIGHT * 0.5 - height * 0.5; j < MAP_HEIGHT * 0.5 + height * 0.5; j++) {
			_map[i][j] = gameLife.getCell(i, j);
			if (_map[i][j] == '1')
				nbGroundTile++;
		}
	}
	if (nbGroundTile < width * height / 8) {
		std::cout << "Not enough ground tile, generating new map" << std::endl;
		return ;
	}
	_nbCollectibleMax = NB_MAX_COLLECTIBLE(width, height);
	_nbCollectibleMin = NB_MIN_COLLECTIBLE(width, height);

	_findIsland();
	std::cout << "Number of island: " << _nbIsland << std::endl;
	_placeMapStart();
	_placeMapEnemy();
	_placeMapCollectible();
	_verifyMapElement();
	_copyMap(newMap);
}

void	MapGenerator::generateMapElement(char map[MAP_WIDTH][MAP_HEIGHT]) {
	_clearMapElement();
	_placeMapStart();
	_placeMapEnemy();
	_placeMapCollectible();
	_verifyMapElement();
	_copyMap(map);
}

void	MapGenerator::generateCollectible(char map[MAP_WIDTH][MAP_HEIGHT]) {
	_clearMapCollectible();
	_placeMapCollectible();
	_verifyMapElement();
	_copyMap(map);
}

void	MapGenerator::generateCollectible(char map[MAP_WIDTH][MAP_HEIGHT], uint32_t nbCollectible) {
	_clearMapCollectible();
	_placeMapCollectible(nbCollectible);
	_verifyMapElement();
	_copyMap(map);
}

void	MapGenerator::generateStart(char map[MAP_WIDTH][MAP_HEIGHT]) {
	_map[_start.x][_start.y] = '1';
	_placeMapStart();
	_verifyMapElement();
	_copyMap(map);
}

void	MapGenerator::generateEnemy(char map[MAP_WIDTH][MAP_HEIGHT]) {
	_map[_enemy.x][_enemy.y] = '1';
	_placeMapEnemy();
	_verifyMapElement();
	_copyMap(map);
}

//Private

#include <fstream>

void MapGenerator::_findIsland() {
	_nbIsland = 0;
	_surfaces.clear();
	_surfaces.push_back(_mapIslandSurface(0, 0, '0'));
	int totalSurface = MAP_WIDTH * MAP_HEIGHT;
	if (_surfaces[0] == totalSurface) return;

	std::ofstream file("test.txt", std::ios::out | std::ios::trunc);  //déclaration du flux et ouverture du fichier
    if (!file) {
    	std::cerr << "Erreur à l'ouverture !" << std::endl;
        return ;
	}

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			if (!_mapping[i][j]) {
				if (_map[i][j] == '0')
					_surfaces[0] += _mapIslandSurface(i, j, '0');
				else {
					_nbIsland++;
					_surfaces.push_back(_mapIslandSurface(i, j, '1'));
				}
				file << std::endl;
				file << "Map" << std::endl;
				file << std::endl;
				for (int i = 0; i < MAP_WIDTH; i++) {
					for (int j = 0; j < MAP_HEIGHT; j++) {
						file << _map[i][j];
					}
					file << std::endl;
				}
				file << std::endl;
				file << "Mapped" << std::endl;
				file << std::endl;
				for (int i = 0; i < MAP_WIDTH; i++) {
					for (int j = 0; j < MAP_HEIGHT; j++) {
						file << _mapping[i][j];
					}
					file << std::endl;
				}
				file << std::endl;
				std::cout << "Maped surface: " << _getSumSurfaces() << " total: " << totalSurface << std::endl;
				
				if (_getSumSurfaces() >= totalSurface)
					return;
				
			}
		}
	}

	if (file)
		file.close();
}

int MapGenerator::_mapIslandSurface(int x, int y, char depth) {
	if (_map[x][y] != depth || _mapping[x][y])
		return 0;
	if (depth == '0')
		_mapping[x][y] = 1;
	else 
		_mapping[x][y] = _nbIsland + 1;
	int nbGroundTile = 1;
	nbGroundTile += _mapIslandSurface(x + 1, y, depth);
	nbGroundTile += _mapIslandSurface(x - 1, y, depth);
	nbGroundTile += _mapIslandSurface(x, y + 1, depth);
	nbGroundTile += _mapIslandSurface(x, y - 1, depth);
	return nbGroundTile;
}

int MapGenerator::_getSumSurfaces() {
	int sum = 0;
	
	int biggestSurface = _surfaces[1];
	for (long unsigned int i = 0; i < _surfaces.size(); i++) {
		sum += _surfaces[i];
		std::cout << "Surface " << i << ": " << _surfaces[i] << std::endl;
	}
	return sum;
}

void MapGenerator::_placeMapStart() {
	do {
		int side = rand() % 4;
		int dir;
		if (side == 0 || side == 1)
			dir = -1;
		else
			dir = 1;

		int pos;
		if (side % 2)
			pos = rand() % (MAP_WIDTH - MAP_MARGING * 4) + MAP_MARGING * 2;
		else
			pos = rand() % (MAP_HEIGHT - MAP_MARGING * 4) + MAP_MARGING * 2;
		_start = _findLandFromBorder(side, pos, dir);
		if (_start.x != -1) {
			_map[_start.x][_start.y] = 'S';
			_playerIsland = _mapping[_start.x][_start.y];
		}
	} while (_start.x == -1);
}

void MapGenerator::_placeMapEnemy() {
	t_veci vec;
	do {
		vec = (t_veci){.x = rand() % MAP_WIDTH, .y = rand() % MAP_HEIGHT};
	} while (_map[vec.x][vec.y] != '1');
	_map[vec.x][vec.y] = 'E';
	_enemy = vec;
}

void MapGenerator::_placeMapCollectible() {
	_nbCollectible = (rand() % (int)(_nbCollectibleMax - _nbCollectibleMin)) + _nbCollectibleMin;
	for (uint32_t i = 0; i < _nbCollectible; i++) {
		t_veci vec;
		do {
			vec = (t_veci){.x = rand() % MAP_WIDTH, .y = rand() % MAP_HEIGHT};
		} while (_map[vec.x][vec.y] != '1');
		_map[vec.x][vec.y] = 'C';
	}
}

void MapGenerator::_placeMapCollectible(uint32_t nbCollectible) {
	_nbCollectible = nbCollectible;
	for (uint32_t i = 0; i < _nbCollectible; i++) {
		t_veci vec;
		do {
			vec = (t_veci){.x = rand() % MAP_WIDTH, .y = rand() % MAP_HEIGHT};
		} while (_map[vec.x][vec.y] != '1');
		_map[vec.x][vec.y] = 'C';
	}
}


void MapGenerator::_verifyMapElement() {
	char tmp[MAP_WIDTH][MAP_HEIGHT];
	do {
		_copyMap(tmp);
		_isEnemyValid = false;
		_isAtLeastOneCollectible = false;
		_spreadingVerifAlgorithm(tmp, _start);
		if (! _isEnemyValid)
			_placeMapEnemy();
		if (! _isAtLeastOneCollectible)
			_placeMapCollectible();
	} while (!_isEnemyValid || !_isAtLeastOneCollectible);
	_clearWrongMapElement(tmp);
}

t_veci MapGenerator::_findLandFromBorder(int side, int pos, int dir) {
	t_veci vec;
	if (side % 2) {
		if (dir == -1)
			vec = (t_veci){.x = pos, .y = MAP_HEIGHT};
		else
			vec = (t_veci){.x = pos, .y = 0};
	}
	else {
		if (dir == -1)
			vec = (t_veci){.x = 0, .y = pos};
		else
			vec = (t_veci){.x = MAP_WIDTH, .y = pos};
	}
	
	do {
		if (side % 2) {
			vec.y += dir;
			if (vec.y < 0 || vec.y >= MAP_HEIGHT)
				return (t_veci){.x = -1, .y = -1};
		}
		else {
			vec.x += dir;
			if (vec.x < 0 || vec.x >= MAP_WIDTH)
				return (t_veci){.x = -1, .y = -1};
		}
	} while (_map[vec.x][vec.y] != '1');

	return vec;
}

void MapGenerator::_spreadingVerifAlgorithm(char map[MAP_WIDTH][MAP_HEIGHT], t_veci vec) {
	if (map[vec.x][vec.y] == '0' || map[vec.x][vec.y] == '.')
		return ;
	if (!_isEnemyValid && map[vec.x][vec.y] == 'E')
		_isEnemyValid = true;
	if (!_isAtLeastOneCollectible && map[vec.x][vec.y] == 'C')
		_isAtLeastOneCollectible = true;
	map[vec.x][vec.y] = '.';
	_spreadingVerifAlgorithm(map, (t_veci){.x = vec.x + 1, .y = vec.y});
	_spreadingVerifAlgorithm(map, (t_veci){.x = vec.x - 1, .y = vec.y});
	_spreadingVerifAlgorithm(map, (t_veci){.x = vec.x, .y = vec.y + 1});
	_spreadingVerifAlgorithm(map, (t_veci){.x = vec.x, .y = vec.y - 1});
}

void MapGenerator::_copyMap(char dst[MAP_WIDTH][MAP_HEIGHT]) {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			dst[i][j] = _map[i][j];
		}
	}
}

void MapGenerator::_copyMapping(char dst[MAP_WIDTH][MAP_HEIGHT]) {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			dst[i][j] = _mapping[i][j];
		}
	}
}

void MapGenerator::_clearMap() {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_map[i][j] = '0';
			_mapping[i][j] = 0;
		}
	}
}

void MapGenerator::_clearMapping() {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_mapping[i][j] = 0;
		}
	}
}

void MapGenerator::_clearWrongMapElement(char mapVerified[MAP_WIDTH][MAP_HEIGHT]) {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {

			if (mapVerified[i][j] == 'C' || mapVerified[i][j] == 'E')
				_map[i][j] = '1';
		}
	}
}

void MapGenerator::_clearMapElement() {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			if (_map[i][j] == 'C' || _map[i][j] == 'E' || _map[i][j] == 'S')
				_map[i][j] = '1';
		}
	}
}

void MapGenerator::_clearMapCollectible() {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			if (_map[i][j] == 'C')
				_map[i][j] = '1';
		}
	}
}

//Unused

MapGenerator::MapGenerator(MapGenerator const &src) {
	std::cout << "MapGenerator copy constructor called" << std::endl;
	*this = src;
}

MapGenerator &MapGenerator::operator=(MapGenerator const &rhs) {
	std::cout << "MapGenerator assignment operator called" << std::endl;
	if (this != &rhs) {
		(void)rhs;
	}
	return (*this);
}