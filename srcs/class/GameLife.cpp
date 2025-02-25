#include "GameLife.hpp"

GameLife::GameLife(){
	std::cout << "GameLife constructor called" << std::endl;
}

GameLife::~GameLife() {
	std::cout << "GameLife destructor called" << std::endl;
}

GameLife::GameLife(GameLife const &src) {
	std::cout << "GameLife copy constructor called" << std::endl;
	*this = src;
}

GameLife &GameLife::operator=(GameLife const &rhs) {
	std::cout << "GameLife assignment operator called" << std::endl;
	if (this != &rhs) {
		for (int32_t i = 0; i < MAP_WIDTH; i++) {
			for (int32_t j = 0; j < MAP_HEIGHT; j++) {
				_grid[i][j] = rhs._grid[i][j];
			}
		}
	}
	return (*this);
}

void GameLife::generateGrid() {
	std::cout << "GameLife generateGrid called" << std::endl;
	_generating = true;
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_grid[i][j] = '0';
		}
	}
	int nbCellToPlace = (MAP_WIDTH * MAP_HEIGHT) * 0.55;
	for (int i = 0; i < nbCellToPlace; i++) {
		bool isAlive;
		do {
			isAlive = false;
			int x = rand() % MAP_WIDTH;
			int y = rand() % MAP_HEIGHT;
			if (_grid[x][y] == '1') {
				isAlive = true;
			}
			else {
				_grid[x][y] = '1';
			}

		} while (isAlive);
	}
	_generating = false;
}

void GameLife::updateLife() {
	if (_isGenerating()) {
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
}

void GameLife::displayAliveCell(void *MLXSetup, mlx_image_t	*cell) const {
	MLXWrapper *mlx = static_cast<MLXWrapper *>(MLXSetup);
	
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			if (_grid[i][j] == '1') {
				mlx->imageToWindow(cell, i * TILE_SIZE, j * TILE_SIZE);
			}
		}
	}
}

char GameLife::_getCellState(int32_t x, int32_t y) const {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return ('0');
	return (_grid[x][y]);
}

int GameLife::_countAliveNeighbours(int32_t x, int32_t y) const {
	int count = 0;
	for (int32_t i = -1; i <= 1; i++) {
		for (int32_t j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)
				continue;
			if (_getCellState(x + i, y + j) != '0')
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
