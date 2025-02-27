#ifndef MAPGENERATOR_HPP
# define MAPGENERATOR_HPP

#include "GameLife.hpp"

class MapGenerator {
public:
	MapGenerator();
	~MapGenerator();

	void	generateMap(char newMap[MAP_WIDTH][MAP_HEIGHT]);

private:
	char	_map[MAP_WIDTH][MAP_HEIGHT];
	int		_nbCollectible;
	t_veci	_start;
	t_veci	_enemy;
	bool	_isEnemyValid;
	bool	_isAtLeastOneCollectible;

	void		_placeMapStart();
	void		_placeMapEnemy();
	void		_placeMapElement();
	void		_verifyMapElement();

	t_veci		_findLandFromBorder(int side, int pos, int dir);
	void		_spreadingVerifAlgorithm(char map[MAP_WIDTH][MAP_HEIGHT], t_veci vec);
	void		_copyMap(char dst[MAP_WIDTH][MAP_HEIGHT], char src[MAP_WIDTH][MAP_HEIGHT]);
	void		_clearWrongMapElement(char mapVerified[MAP_WIDTH][MAP_HEIGHT]);


	MapGenerator(MapGenerator const &src);
	MapGenerator &operator=(MapGenerator const &rhs);
};



#endif