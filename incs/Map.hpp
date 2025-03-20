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

	void	generateMap();
	void	generateMap(float density);

	void	generateMapElement();
	void	generateCollectible();
	void	genrateStart();
	void	generateEnemy();
	void	generateMapGrass();
	void	generateMapGrass(float density);
	void	generateMapGrassBig();
	void	generateMapGrassBig(float density);

	int		getNbCollectible() const { return _nbCollectible; }
	void	setNbCollectible(uint32_t nbCollectible);
	int		getNbCollectibleLeft() { return _nbCollectible; }
	t_veci	getSpawn() const { return _start; }
	t_veci	getEnemy() const { return _enemy; }
	char	getCell(int x, int y);
	char	getCellGrass(int x, int y);
	char	getCellGrassBig(int x, int y);

private:
	char			_map[MAP_WIDTH][MAP_HEIGHT];
	char			_mapGrass[MAP_WIDTH][MAP_HEIGHT];
	char			_mapGrassBig[MAP_GRASS_WIDTH][MAP_GRASS_HEIGHT];
	MapGenerator	_mapGenerator;
	uint32_t		_nbCollectible;
	int				_nbCollectibleLeft;
	t_veci			_start;
	t_veci			_enemy;

	bool			_mapCreated;

	void			_parseMapElement();
};

void displayMapImage(mlx_image_t *map_img, Map &map, t_mapDisplay *mapDisplay);

#endif