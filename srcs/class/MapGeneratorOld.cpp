#include "MapGenerator.hpp"

//Constructor

MapGenerator::MapGenerator() {
}

MapGenerator::~MapGenerator() {
}

//Public

void MapGenerator::getNewMap(char newMap[MAP_WIDTH][MAP_HEIGHT]){
	_generateMap();
	_copyMap(newMap);
}

// Private

void	MapGenerator::_generateMap() {
	uint32_t width = (rand() % (int)(MAP_WIDTH - MAP_WIDTH_MIN)) + MAP_WIDTH_MIN;
	uint32_t height = (rand() % (int)(MAP_HEIGHT - MAP_HEIGHT_MIN)) + MAP_HEIGHT_MIN;

	_nbCollectibleMax = NB_MAX_COLLECTIBLE(width, height);
	_nbCollectibleMin = NB_MIN_COLLECTIBLE(width, height);

	_clearMap();

	GameLife gameLife(width, height, MAP_DENSITY);
	gameLife.generateGrid();
	gameLife.updateLife(25);

	uint32_t nbGroundTile = 0;
	for (int32_t i = MAP_WIDTH * 0.5 - width * 0.5; i < MAP_WIDTH * 0.5 + width * 0.5; i++) {
		for (int32_t j = MAP_HEIGHT * 0.5 - height * 0.5; j < MAP_HEIGHT * 0.5 + height * 0.5; j++) {
			_map[i][j] = gameLife.getCell(i, j);
			if (_map[i][j] == '1')
				nbGroundTile++;
		}
	}
	if (nbGroundTile < width * height / 8)
		return ;

	_mapIslands();
	_placeMapElements();
	// std::cout << "Map generated (Size: " << width << ", " << height << ")" << std::endl;
}


void MapGenerator::_mapIslands() {
	_nbIsland = 0;
	_mainIsland = 0;
	_playerIsland = 0;
	_surfaces.clear();
	_surfaces.push_back(_mapIslandSurface(0, 0, '0'));
	int totalSurface = MAP_WIDTH * MAP_HEIGHT;
	if (_surfaces[0] == totalSurface) return;

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			if (!_mapping[i][j]) {
				if (_map[i][j] == '0')
					_surfaces[0] += _mapIslandSurface(i, j, '3');
				else {
					_nbIsland++;
					_surfaces.push_back(_mapIslandSurface(i, j, '1'));
					if (_nbIsland == 1)
						_mainIsland = 1;
					else if (_surfaces[_nbIsland] > _surfaces[_mainIsland])
						_mainIsland = _nbIsland;
				}
				if (_getSumSurfaces() >= totalSurface)
					return;
			}
		}
	}
}

void MapGenerator::_placeMapElements() {
	_placeMapStart();
	if (_nbIsland > 1 && _playerIsland != _mainIsland)
		_placeBridge(_mainIsland, _playerIsland);
	int similarIsland = _isSimilarIsland();
	if (similarIsland)
		_placeBridge(similarIsland, _mainIsland);
	while (!_verifyMapAccessibility()) {
		_map[_start.x][_start.y] = '1';
		_placeMapStart();
	}
	_placeStartBridge();
	_placeMapEnemy();
	_placeMapCollectible();
	_verifyMapElement();
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
			_playerIsland = _mapping[_start.x][_start.y] - 1;
		}
	} while (_start.x == -1);
}

void MapGenerator::_placeBridge(int islandStart, int islandEnd) {
	t_veci pointA = _findLandFromIsland(islandStart);
	t_veci pointB = _findLandFromIsland(islandEnd);

	_findBridgePoint(pointA, pointB, islandStart, islandEnd);

	std::vector<t_veci> bridge;

	int dx = abs(pointA.x - pointB.x);
	int dy = abs(pointA.y - pointB.y);
	int sx = (pointB.x < pointA.x) ? 1 : -1;
	int sy = (pointB.y < pointA.y) ? 1 : -1;

	int x = pointB.x;
	int y = pointB.y;
	int errX = 0;
	int errY = 0;
	int bridgeStart = 0;
	int bridgeEnd = dx + dy;

	for (int i = 0; i <= dx + dy; i++) {
		bridge.push_back((t_veci){.x = x, .y = y});
		if (_isOtherLandNear(x, y, islandStart)){
			bridgeEnd = i + 1;
			break;
		}
		if (_isOtherLandNear(x, y, islandEnd)) {
			bridgeStart = i;
		}
		if ((errX + 1) * dy < (errY + 1) * dx) {
			x += sx;
			errX++;
		} else {
			y += sy;
			errY++;
		}
	}
	for (int i = bridgeStart; i < bridgeEnd; i++) {
		if (_map[bridge[i].x][bridge[i].y] == '0')
			_map[bridge[i].x][bridge[i].y] = '2';
	}
}

void MapGenerator::_placeStartBridge() {
	if (_startAcces == 0) {
		_map[_start.x + 1][_start.y] = '2';
	} else if (_startAcces == 1) {
		_map[_start.x][_start.y + 1] = '2';
	} else if (_startAcces == 2) {
		_map[_start.x - 1][_start.y] = '2';
	} else if (_startAcces == 3) {
		_map[_start.x][_start.y - 1] = '2';
	}
}

bool MapGenerator::_verifyMapAccessibility() {
	int x = _start.x;
	int y = 0;
	_startAcces = 3;
	while (y != _start.y + 1) {
		if (_map[x][y] == '1')
			break;
		if (_map[x][y] == 'S')
			return true;
		y++;
	}
	y = MAP_HEIGHT - 1;
	_startAcces = 1;
	while (y != _start.y - 1) {
		if (_map[x][y] == '1')
			break;
		if (_map[x][y] == 'S')
			return true;
		y--;
	}
	y = _start.y;
	x = 0;
	_startAcces = 2;
	while (x != _start.x + 1) {
		if (_map[x][y] == '1')
			break;
		if (_map[x][y] == 'S')
			return true;
		x++;
	}
	x = MAP_WIDTH - 1;
	_startAcces = 0;
	while (x!= _start.x - 1) {
		if (_map[x][y] == '1')
			break;
		if (_map[x][y] == 'S')
			return true;
		x--;
	}
	return false;
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

int MapGenerator::_mapIslandSurface(int x, int y, char depth) {
	if (depth == '3' && _map[x][y] == '0')
		_map[x][y] = '3';
	if (_map[x][y] != depth || _mapping[x][y])
		return 0;
	if (depth == '0' || depth == '3')
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

	for (long unsigned int i = 0; i < _surfaces.size(); i++) {
		sum += _surfaces[i];
	}
	return sum;
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

t_veci MapGenerator::_findLandFromIsland(int island) {
	t_veci vec;
	do {
		vec = (t_veci){.x = rand() % MAP_WIDTH, .y = rand() % MAP_HEIGHT};
	} while (_mapping[vec.x][vec.y] != island + 1);
	return vec;
}

void MapGenerator::_findBridgePoint(t_veci &bridgeStart, t_veci &bridgeEnd, int islandStart, int islandEnd) {
	int dx = abs(bridgeEnd.x - bridgeStart.x);
	int dy = abs(bridgeEnd.y - bridgeStart.y);
	int sx = (bridgeStart.x < bridgeEnd.x) ? 1 : -1;
	int sy = (bridgeStart.y < bridgeEnd.y) ? 1 : -1;

	int x = bridgeStart.x;
	int y = bridgeStart.y;
	int errX = 0;
	int errY = 0;

	for (int i = 0; i <= dx + dy; i++) {
		// _map[x][y] = 'X';
		if (_isOtherLandNear(x, y, islandStart))
			bridgeStart = (t_veci){x, y};
		if (_isOtherLandNear(x, y, islandEnd)) {
			bridgeEnd = (t_veci){x, y};
			break;
		}
		if ((errX + 1) * dy < (errY + 1) * dx) {
			x += sx;
			errX++;
		} else {
			y += sy;
			errY++;
		}
	}
}

void MapGenerator::_drawBridge(t_veci from, t_veci to) {
	int dx = abs(to.x - from.x);
	int dy = abs(to.y - from.y);
	int sx = (from.x < to.x) ? 1 : -1;
	int sy = (from.y < to.y) ? 1 : -1;

	int x = from.x;
	int y = from.y;
	int errX = 0;
	int errY = 0;

	for (int i = 0; i <= dx + dy; i++) {
		if (_map[x][y] == '0') {
			_map[x][y] = '2';
		}
		if ((errX + 1) * dy < (errY + 1) * dx) {
			x += sx;
			errX++;
		} else {
			y += sy;
			errY++;
		}
	}
}

int MapGenerator::_isSimilarIsland() {
	if (_nbIsland < 2)
		return 0;
	for (int i = 1; i <= _nbIsland; i++) {
		if (_surfaces[i] >= _surfaces[_mainIsland] * 0.3 && i != _mainIsland && i != _playerIsland) {
			return i;
		}
	}
	return 0;
}

bool MapGenerator::_isOtherLandNear(int x, int y, int island) {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return false;
	// if (_mapping[x][y] != 1)
	// 	return false;

	int sum = 0;
	island++;

	if (x + 1 < MAP_WIDTH && _map[x + 1][y] == '1' && _mapping[x + 1][y] == island)
		sum++;
	if (x - 1 >= 0 && _map[x - 1][y] == '1' && _mapping[x - 1][y] == island)
		sum++;
	if (y + 1 < MAP_HEIGHT && _map[x][y + 1] == '1' && _mapping[x][y + 1] == island)
		sum++;
	if (y - 1 >= 0 && _map[x][y - 1] == '1' && _mapping[x][y - 1] == island)
		sum++;
	return sum > 0;
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