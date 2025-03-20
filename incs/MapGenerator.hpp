#ifndef MAPGENERATOR_HPP
# define MAPGENERATOR_HPP

#include "GameLife.hpp"

class MapGenerator {
public:
	MapGenerator();
	~MapGenerator();

	void		generateMap(char newMap[MAP_WIDTH][MAP_HEIGHT]);
	void		generateMap(char newMap[MAP_WIDTH][MAP_HEIGHT], float density);
	void		generateMapElement(char map[MAP_WIDTH][MAP_HEIGHT]);
	void		generateCollectible(char map[MAP_WIDTH][MAP_HEIGHT]);
	void		generateCollectible(char map[MAP_WIDTH][MAP_HEIGHT], uint32_t nbCollectible);
	void		generateStart(char map[MAP_WIDTH][MAP_HEIGHT]);
	void		generateEnemy(char map[MAP_WIDTH][MAP_HEIGHT]);

private:
	char		_map[MAP_WIDTH][MAP_HEIGHT];
	uint32_t	_nbCollectible;
	t_veci		_start;
	t_veci		_enemy;
	bool		_isEnemyValid;
	bool		_isAtLeastOneCollectible;

	void		_placeMapStart();
	void		_placeMapEnemy();
	void		_placeMapCollectible();
	void		_placeMapCollectible(uint32_t nbCollectible);
	void		_verifyMapElement();

	t_veci		_findLandFromBorder(int side, int pos, int dir);
	void		_spreadingVerifAlgorithm(char map[MAP_WIDTH][MAP_HEIGHT], t_veci vec);
	void		_copyMap(char dst[MAP_WIDTH][MAP_HEIGHT]);
	void		_clearWrongMapElement(char mapVerified[MAP_WIDTH][MAP_HEIGHT]);
	void		_clearMapElement();
	void		_clearMapCollectible();

	MapGenerator(MapGenerator const &src);
	MapGenerator &operator=(MapGenerator const &rhs);
};



#endif