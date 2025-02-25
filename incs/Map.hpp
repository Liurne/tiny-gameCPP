#ifndef MAP_HPP
# define MAP_HPP

#include "game_rule.h"
#include "MLXWrapper.hpp"

class Map {
public:
	Map();
	~Map();
	Map(Map const &src);
	Map &operator=(Map const &rhs);

	void	generateMap();

	char	**getMap() const { return ((char **)_map); }

private:
	char		_map[MAP_WIDTH][MAP_HEIGHT];
};

#endif