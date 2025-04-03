#ifndef GAMELIFE_HPP
# define GAMELIFE_HPP

#include "game_rule.h"
#include "MLXWrapper.hpp"

class GameLife {
public:
	GameLife();
	GameLife(uint32_t width, uint32_t height, float density);
	~GameLife();

	void	generateGrid();
	void	updateLife();
	void	updateLife(uint32_t iterations);
	void	displayAliveCell(mlx_image_t *renderer, uint32_t cell_size) const;

	char 	getCell(uint32_t x, uint32_t y) const;

private:
	std::vector<std::vector<char> >	_grid;
	uint32_t						_width;
	uint32_t						_height;
	float							_density;
	bool							_isGenerating;

	int		_countAliveNeighbours(int32_t x, int32_t y) const;
	bool	_isAlive(int32_t x, int32_t y) const;
	bool	_isDead(int32_t x, int32_t y) const;
	
	GameLife(GameLife const &src);
	GameLife &operator=(GameLife const &rhs);
};

#endif