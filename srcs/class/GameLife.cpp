#include "GameLife.hpp"

//Public

GameLife::GameLife() : _isGenerating(false) {
	std::cout << "GameLife constructor called" << std::endl;
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_grid[i][j] = '0';
		}
	}
}

GameLife::~GameLife() {
	std::cout << "GameLife destructor called" << std::endl;
}

void GameLife::generateGrid() {
	std::cout << "GameLife generateGrid called" << std::endl;
	_isGenerating = true;
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_grid[i][j] = '0';
		}
	}
	int nbCellToPlace = ((MAP_WIDTH - MAP_MARGING * 2) * (MAP_HEIGHT - MAP_MARGING * 2)) * 0.55;
	for (int i = 0; i < nbCellToPlace; i++) {
		t_veci vec;
		do {
			vec.x = (rand() % (MAP_WIDTH - MAP_MARGING * 2)) + MAP_MARGING;
			vec.y = (rand() % (MAP_HEIGHT - MAP_MARGING * 2)) + MAP_MARGING;
		} while (_grid[vec.x][vec.y] == '1');
		_grid[vec.x][vec.y] = '1';
	}
	_isGenerating = false;
}

void GameLife::updateLife() {
	if (_isGenerating) {
		return ;
	}
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			if (_grid[i][j] == '1' && _isDead(i, j)) {
				_grid[i][j] = '0';
			}
			else if (_grid[i][j] == '0' && _isAlive(i, j)) {
				_grid[i][j] = '1';
				
			}
		}
	}
	usleep(5000);
}

void GameLife::displayAliveCell(mlx_image_t *renderer) const {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			if (_grid[i][j] == '1') {
				draw_rect(renderer, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0xFFFFFFFF);
			}
		}
	}
}

char	GameLife::getCell(uint32_t x, uint32_t y) const {
	if (x > MAP_WIDTH || y > MAP_HEIGHT)
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

//Useless

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
