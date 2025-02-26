#ifndef MAPGENERATOR_HPP
# define MAPGENERATOR_HPP

#include "Map.hpp"
#include "GameLife.hpp"

class MapGenerator {
public:
	MapGenerator();
	~MapGenerator();
	MapGenerator(MapGenerator const &src);
	MapGenerator &operator=(MapGenerator const &rhs);

	void	generateMap();
	void	displayMap(mlx_image_t *renderer) const;

	char	**getMap() const { return ((char **)_map); }

private:
	char	_map[MAP_WIDTH][MAP_HEIGHT];

	void		_placeMapStart();
	void		_placeMapExit();
	void		_placeMapElement();
	void		_verifyMapElement();
	void		_clearWrongMapElement();
};



#endif