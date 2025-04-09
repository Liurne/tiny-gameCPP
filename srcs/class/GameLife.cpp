#include "GameLife.hpp"

//Public

GameLife::GameLife() : _width(MAP_WIDTH), _height(MAP_HEIGHT), _density(MAP_DENSITY), _isGenerating(false) {
	std::cout << "GameLife constructor called" << std::endl;
	for (uint32_t i = 0; i < MAP_WIDTH; i++) {
		_grid.push_back(std::vector<char>());
		for (uint32_t j = 0; j < MAP_HEIGHT; j++) {
			_grid[i].push_back('0');
		}
	}
}

GameLife::GameLife(uint32_t width, uint32_t height, float density) : _width(width), _height(height), _density(density), _isGenerating(false) {
	std::cout << "GameLife constructor called" << std::endl;
	for (uint32_t i = 0; i < width; i++) {
		_grid.push_back(std::vector<char>());
		for (uint32_t j = 0; j < height; j++) {
			_grid[i].push_back('0');
		}
	}
}

GameLife::~GameLife() {
	std::cout << "GameLife destructor called" << std::endl;
}

void GameLife::generateGrid() {
	_isGenerating = true;
	for (uint32_t i = 0; i < _width; i++) {
		for (uint32_t j = 0; j < _height; j++) {
			_grid[i][j] = '0';
		}
	}
	int nbCellToPlace = ((_width - MAP_MARGING * 2) * (_height - MAP_MARGING * 2)) * _density;
	for (int i = 0; i < nbCellToPlace; i++) {
		t_veci vec;
		do {
			vec.x = (rand() % (_width - MAP_MARGING * 2)) + MAP_MARGING;
			vec.y = (rand() % (_height - MAP_MARGING * 2)) + MAP_MARGING;
		} while (_grid[vec.x][vec.y] == '1');
		_grid[vec.x][vec.y] = '1';
	}
	_isGenerating = false;
}

void GameLife::generateGrid(uint32_t width, uint32_t height, float density) {
	_isGenerating = true;
	_createGrid(width, height, density);
	for (uint32_t i = 0; i < _width; i++) {
		for (uint32_t j = 0; j < _height; j++) {
			_grid[i][j] = '0';
		}
	}
	int nbCellToPlace = ((_width - MAP_MARGING * 2) * (_height - MAP_MARGING * 2)) * _density;
	for (int i = 0; i < nbCellToPlace; i++) {
		t_veci vec;
		do {
			vec.x = (rand() % (_width - MAP_MARGING * 2)) + MAP_MARGING;
			vec.y = (rand() % (_height - MAP_MARGING * 2)) + MAP_MARGING;
		} while (_grid[vec.x][vec.y] == '1');
		_grid[vec.x][vec.y] = '1';
	}
	_isGenerating = false;
}

void GameLife::updateLife() {
	if (_isGenerating) {
		return ;
	}
	for (uint32_t i = 0; i < _width; i++) {
		for (uint32_t j = 0; j < _height; j++) {
			if (_grid[i][j] == '1' && _isDead(i, j)) {
				_grid[i][j] = '0';
			}
			else if (_grid[i][j] == '0' && _isAlive(i, j)) {
				_grid[i][j] = '1';
			}
		}
	}
}

void GameLife::updateLife(uint32_t iterations) {
	if (_isGenerating) {
		return ;
	}
	for (uint32_t k = 0; k < iterations; k++) {
		for (uint32_t i = 0; i < _width; i++) {
			for (uint32_t j = 0; j < _height; j++) {
				if (_grid[i][j] == '1' && _isDead(i, j)) {
					_grid[i][j] = '0';
				}
				else if (_grid[i][j] == '0' && _isAlive(i, j)) {
					_grid[i][j] = '1';
				}
			}
		}
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
