#ifndef MAP_HPP
# define MAP_HPP

#include "game_rule.h"
#include "MLXWrapper.hpp"

class Map {
public:
	Map(char **map, int width, int height);
	~Map();
	Map(Map const &src);
	Map &operator=(Map const &rhs);

	void	generateMap();
	void	displayMap(mlx_image_t *renderer) const;

	char	**getMap() const { return ((char **)_map); }

private:
	char		_map[MAP_WIDTH][MAP_HEIGHT];
	int			_nbCollectible;
	t_veci		_start;
	t_veci		_exit;
	Map();

};

#endif