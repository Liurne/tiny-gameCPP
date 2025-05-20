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

	void	initView(MLXWrapper &mlx);

	void	generateMap();

	void 	generateMapDeep();
	void	generateMapGrass();
	void	generateMapFlower();

	int		getNbCollectible() const { return _nbCollectible; }
	t_veci	getSpawn() const { return _start; }
	t_veci	getEnemy() const { return _enemy; }
	char	getCell(int x, int y) const;
	char	getCellDeep(int x, int y) const;
	char	getCellGrass(int x, int y) const;
	char	getCellFlower(int x, int y) const;
	char	getCellRandom(int x, int y) const;

private:
	char			_map[MAP_WIDTH][MAP_HEIGHT];
	char			_mapDeep[MAP_WIDTH][MAP_HEIGHT];
	char			_mapGrass[MAP_WIDTH][MAP_HEIGHT];
	char			_mapFlower[MAP_WIDTH][MAP_HEIGHT];
	char			_mapRandom[MAP_WIDTH][MAP_HEIGHT];
	MapGenerator	_mapGenerator;
	uint32_t		_nbCollectible;
	int				_nbCollectibleLeft;
	t_veci			_start;
	t_veci			_enemy;

	bool			_mapCreated;

	mlx_image_t		*_mapView;

	void			_parseMapElement();
	void			_createMapView();
};

void displayMapImage(mlx_image_t *map_img, Map &map, t_mapDisplay *mapDisplay);

#endif