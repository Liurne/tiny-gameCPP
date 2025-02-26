#ifndef GAMELIFE_HPP
# define GAMELIFE_HPP

#include "game_rule.h"
#include "MLXWrapper.hpp"

class GameLife {
public:
	GameLife();
	~GameLife();
	GameLife(GameLife const &src);
	GameLife &operator=(GameLife const &rhs);

	void	generateGrid();
	void	updateLife();
	void	displayAliveCell(mlx_image_t *renderer,mlx_image_t *cell) const;

	char	**getGrid() const { return ((char **)_grid); }

private:
	char		_grid[MAP_WIDTH+2][MAP_HEIGHT+2];
	bool		_generating;

	bool	_isGenerating() const { return (_generating); }
	char	_getCellState(int32_t x, int32_t y) const;
	int		_countAliveNeighbours(int32_t x, int32_t y) const;
	bool	_isAlive(int32_t x, int32_t y) const;
	bool	_isDead(int32_t x, int32_t y) const;
};

#endif