#ifndef MAP_HPP
# define MAP_HPP

#include "game_rule.h"

class Map {
public:
	Map();
	~Map();
	Map(Map const &src);
	Map &operator=(Map const &rhs);

	int32_t		getWidth() const;
	int32_t		getHeight() const;

private:
	char		_map[MAP_WIDTH][MAP_HEIGHT];
	int32_t		_width;
	int32_t		_height;

};

#endif