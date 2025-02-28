#ifndef MAP_HPP
# define MAP_HPP

#include "game_rule.h"
#include "MLXWrapper.hpp"
#include "MapGenerator.hpp"

class Map {
public:
	Map();
	~Map();
	Map(Map const &src);
	Map &operator=(Map const &rhs);

	void	initMap();
	void	displayMap(mlx_image_t *renderer) const;
	void	saveMapToPNG() const;

	int		getNbCollectible() const { return _nbCollectible; }
	int		getNbCollectibleLeft() { return _nbCollectible; }
	t_veci	getSpawn() const { return _start; }
	t_veci	getEnemy() const { return _enemy; }

private:
	char		_map[MAP_WIDTH][MAP_HEIGHT];
	uint32_t	_nbCollectible;
	int			_nbCollectibleLeft;
	t_veci		_start;
	t_veci		_enemy;

	bool		_mapCreated;

	void		_parseMapElement();
};

#endif