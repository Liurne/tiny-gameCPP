#include "GameLife.hpp"

//Public

GameLife::GameLife() : _width(GRID_WIDTH), _height(GRID_HEIGHT), _density(GRID_DENSITY), _isGenerating(false) {
	std::cout << "GameLife constructor called" << std::endl;
	_createGrid(_width, _height, _density);
	generateGrid(_width, _height, _density);
}

GameLife::~GameLife() {
	std::cout << "GameLife destructor called" << std::endl;
}

void GameLife::generateGrid(uint32_t width, uint32_t height, float density) {
	_isGenerating = true;
	_createGrid(width, height, density);

	int nbCellToPlace = ((_width - GRID_MARGING * 2) * (_height - GRID_MARGING * 2)) * _density;
	std::cout << "nbCellToPlace: " << nbCellToPlace << std::endl;
	for (int i = 0; i < nbCellToPlace; i++) {
		t_veci vec;
		do {
			vec.x = (rand() % (_width - GRID_MARGING * 2)) + GRID_MARGING;
			vec.y = (rand() % (_height - GRID_MARGING * 2)) + GRID_MARGING;
		} while (_grid[vec.x][vec.y] == '1');
		_grid[vec.x][vec.y] = '1';
	}
	_isGenerating = false;
}

// void GameLife::generateFragGrid(uint32_t width, uint32_t height, float densityMin, float densityMax) {
// 	_isGenerating = true;
// 	_createGrid(width, height, densityMax);

// 	(void)densityMin; // densityMin is not used in this function, but kept for compatibility with the original code

// 	float density = 0.0f;

// 	std::cout << "densityMax: " << densityMax << std::endl;
// 	std::cout << "densityMin: " << densityMin << std::endl;

// 	density = ((rand() % (int)((densityMax - densityMin) * 100)) + (densityMin * 100)) / 100.0f;
// 	std::cout << "Density: " << density << std::endl;
// 	fillZone(GRID_MARGING, GRID_MARGING, (width / 2) - GRID_MARGING, (height / 2) - GRID_MARGING, density);
// 	// _FillZone(0, 0, (width / 2), (height / 2), density, GRID_MARGING);

// 	density = ((rand() % (int)((densityMax - densityMin) * 100)) + (densityMin * 100)) / 100.0f;
// 	std::cout << "Density: " << density << std::endl;
// 	fillZone((width / 2), GRID_MARGING, (width / 2) - GRID_MARGING, (height / 2) - GRID_MARGING, density);
// 	// _FillZone((width / 2), 0, (width / 2), (height / 2), density, GRID_MARGING);

// 	density = ((rand() % (int)((densityMax - densityMin) * 100)) + (densityMin * 100)) / 100.0f;
// 	std::cout << "Density: " << density << std::endl;
// 	fillZone(GRID_MARGING, (height / 2), (width / 2) - GRID_MARGING, (height / 2) - GRID_MARGING, density);
// 	// _FillZone(0, (height / 2), (width / 2), (height / 2), density, GRID_MARGING);

// 	densityMin = 0.4f;
// 	densityMax = 0.5f;
// 	density = ((rand() % (int)((densityMax - densityMin) * 100)) + (densityMin * 100)) / 100.0f;
// 	std::cout << "Density: " << density << std::endl;
// 	// _FillZone((width / 2), (height / 2), (width / 2) - GRID_MARGING, (height / 2) - GRID_MARGING, density);
// 	fillZone((width / 2), (height / 2), (width / 2), (height / 2), density, GRID_MARGING);

// 	// fillZone(0, 0, width, height, 0.5, GRID_MARGING);
// 	// clearZone((width / 2) - (width / 8), (height / 2) - (height / 8), width/4, height/4);
// 	// fillZone((width / 2) - (width / 4), (height / 2) - (height / 4), width/2, height/2, 0.2);


// 	_isGenerating = false;
// }

void GameLife::clearZone(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	if (x >= _width || y >= _height || x + width > _width || y + height > _height)
		throw std::out_of_range("ClearZone: Out of grid bounds");
	for (uint32_t i = x; i < x + width; i++) {
		for (uint32_t j = y; j < y + height; j++) {
			_grid[i][j] = '0';
		}
	}
}

void GameLife::fillZone(uint32_t x, uint32_t y, uint32_t width, uint32_t height, float density) {
	if (x > _width - GRID_MARGING || y > _height - GRID_MARGING || x + width > _width - GRID_MARGING || y + height > _height - GRID_MARGING)
		throw std::out_of_range("FillZone: Out of grid bounds");
	int nbCellToPlace = (width * height) * density;
	std::cout << "nbCellToPlace: " << nbCellToPlace << std::endl;
	for (int i = 0; i < nbCellToPlace; i++) {
		t_veci vec;
		do {
			vec.x = (rand() % width) + x;
			vec.y = (rand() % height) + y;
		} while (_grid[vec.x][vec.y] == '1');
		_grid[vec.x][vec.y] = '1';
	}
}

void GameLife::fillZone(uint32_t x, uint32_t y, uint32_t width, uint32_t height, float density, uint32_t marging) {
	if (x >= _width || y >= _height || x + width > _width || y + height > _height)
		throw std::out_of_range("FillZone: Out of grid bounds");
	int nbCellToPlace = ((width - marging * 2) * (height - marging * 2)) * density;
	std::cout << "nbCellToPlace: " << nbCellToPlace << std::endl;
	for (int i = 0; i < nbCellToPlace; i++) {
		t_veci vec;
		do {
			vec.x = (rand() % (width - marging * 2)) + x + marging;
			vec.y = (rand() % (height - marging * 2)) + y + marging;
		} while (_grid[vec.x][vec.y] == '1');
		_grid[vec.x][vec.y] = '1';
	}
}


void GameLife::updateLife() {
	if (_isGenerating) {
		return ;
	}
	std::vector<std::vector<char> > tmp = _createGrid(_width, _height);
	for (uint32_t i = 0; i < _width; i++) {
		for (uint32_t j = 0; j < _height; j++) {
			if (_grid[i][j] == '1' && _isDead(i, j)) {
				tmp[i][j] = '0';
			}
			else if (_grid[i][j] == '0' && _isAlive(i, j)) {
				tmp[i][j] = '1';
			}
			else {
				tmp[i][j] = _grid[i][j];
			}
		}
	}
	_grid = tmp;
}

void GameLife::updateLife(uint32_t iterations) {
	if (_isGenerating) {
		return ;
	}
	for (uint32_t k = 0; k < iterations; k++) {
		updateLife();
	}
}

void GameLife::displayAliveCell(mlx_image_t *renderer,uint32_t cell_size) const {
	for (uint32_t i = 0; i < _width; i++) {
		for (uint32_t j = 0; j < _height; j++) {
			if (_grid[i][j] == '1') {
				draw_rect(renderer, i * cell_size, j * cell_size, cell_size, cell_size, 0xFFFFFFFF);
			}
		}
	}
}

char	GameLife::getCell(uint32_t x, uint32_t y) const {
	if (x >= _width || y >= _height)
		return ('0');
	return (_grid[x][y]);
}

//Private

int GameLife::_countAliveNeighbours(int32_t x, int32_t y) const {
	int count = 0;
	for (int32_t i = -1; i <= 1; i++) {
		for (int32_t j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)
				continue;
			if (getCell(x + i, y + j) != '0')
				count++;
		}
	}
	return (count);
}

bool GameLife::_isAlive(int32_t x, int32_t y) const {
	return (_countAliveNeighbours(x, y) >= 5);
}

bool GameLife::_isDead(int32_t x, int32_t y) const {
	return (_countAliveNeighbours(x, y) < 4);
}

std::vector<std::vector<char> > GameLife::_createGrid(uint32_t width, uint32_t height) {
	std::vector<std::vector<char> > grid;
	grid.resize(width);
	for (uint32_t i = 0; i < width; i++) {
		grid[i].resize(height, '0');
	}
	return grid;
}

void GameLife::_createGrid(uint32_t width, uint32_t height, float density) {
	_width = width;
	_height = height;
	_density = density;
	_grid.clear();
	for (uint32_t i = 0; i < _width; i++) {
		_grid.push_back(std::vector<char>());
		for (uint32_t j = 0; j < _height; j++) {
			_grid[i].push_back('0');
		}
	}
}

//Unused

GameLife::GameLife(GameLife const &src) {
	std::cout << "GameLife copy constructor called" << std::endl;
	*this = src;
}

GameLife &GameLife::operator=(GameLife const &rhs) {
	std::cout << "GameLife assignment operator called" << std::endl;
	if (this != &rhs) {
		(void)rhs;
	}
	return (*this);
}
