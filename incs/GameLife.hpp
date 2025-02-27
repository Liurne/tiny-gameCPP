#ifndef GAMELIFE_HPP
# define GAMELIFE_HPP

#include "game_rule.h"
#include "MLXWrapper.hpp"

class GameLife {
public:
	GameLife();
	~GameLife();

	void	generateGrid();
	void	updateLife();
	void	displayAliveCell(mlx_image_t *renderer) const;

	char 	getCell(uint32_t x, uint32_t y) const;

private:
	char		_grid[MAP_WIDTH][MAP_HEIGHT];
	bool		_isGenerating;

	int		_countAliveNeighbours(int32_t x, int32_t y) const;
	bool	_isAlive(int32_t x, int32_t y) const;
	bool	_isDead(int32_t x, int32_t y) const;
	
	GameLife(GameLife const &src);
	GameLife &operator=(GameLife const &rhs);
};

#endif