#ifndef MAPGENERATOR_HPP
# define MAPGENERATOR_HPP

#include "GameLife.hpp"

class MapGenerator {
public:
	MapGenerator();
	~MapGenerator();

	void		getNewMap(char newMap[MAP_WIDTH][MAP_HEIGHT]);


private:
	char		_map[MAP_WIDTH][MAP_HEIGHT];
	uint32_t	_nbCollectible;
	t_veci		_start;
	t_veci		_enemy;

	int			_mapping[MAP_WIDTH][MAP_HEIGHT];
	t_vectori	_surfaces;
	int			_nbIsland;
	int			_playerIsland;
	int			_mainIsland;

	uint32_t	_nbCollectibleMin;
	uint32_t	_nbCollectibleMax;
	bool		_isEnemyValid;
	bool		_isAtLeastOneCollectible;

	void		_generateMap();
	void		_mapIslands();

	void		_placeMapElements();
	void		_placeMapStart();
	void		_placeBridge(int island1, int island2);
	void		_placeMapEnemy();
	void		_placeMapCollectible();
	void		_placeMapCollectible(uint32_t nbCollectible);
	void		_verifyMapElement();

	int			_mapIslandSurface(int x, int y, char depth = 0);
	int			_getSumSurfaces();
	t_veci		_findLandFromBorder(int side, int pos, int dir);
	t_veci		_findLandFromIsland(int island);
	int			_isSimilarIsland();
	void		_spreadingVerifAlgorithm(char map[MAP_WIDTH][MAP_HEIGHT], t_veci vec);
	void		_copyMap(char dst[MAP_WIDTH][MAP_HEIGHT]);
	void		_copyMapping(char dst[MAP_WIDTH][MAP_HEIGHT]);
	void		_clearMap();
	void		_clearMapping();
	void		_clearWrongMapElement(char mapVerified[MAP_WIDTH][MAP_HEIGHT]);
	void		_clearMapElement();
	void		_clearMapCollectible();


	MapGenerator(MapGenerator const &src);
	MapGenerator &operator=(MapGenerator const &rhs);
};



#endif