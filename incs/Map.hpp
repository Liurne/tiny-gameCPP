#ifndef MAP_HPP
# define MAP_HPP

#include "game_rule.h"
#include "MLXWrapper.hpp"
#include "GameLife.hpp"

class Map {
public:
	Map();
	~Map();
	Map(Map const &src);
	Map &operator=(Map const &rhs);

	void	generateMap();
	void	displayMap(mlx_image_t *renderer) const;

	char	**getMap() const { return ((char **)_map); }

private:
	char		_map[MAP_WIDTH][MAP_HEIGHT];

	void		_placeMapStart();
	void		_placeMapExit();
	void		_placeMapElement();
	void		_verifyMapElement();
	void		_clearWrongMapElement();
};

#endif