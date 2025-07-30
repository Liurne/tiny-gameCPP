#ifndef MAPTOOLS_HPP
# define MAPTOOLS_HPP

# include "map/GameLife.hpp"
# include "map/Map.hpp"

class MapTools {
public:
	~MapTools();

	static Map	*generateMap();
	static void	generateView(Map *map, mlx_image_t *image);

private:
	typedef enum {
		BASIC_ISLAND = 0,
		CRESCENT_ISLAND = 1,
		LAKE_ISLAND = 2,
		ARCHIPELAGO = 3,
	} t_island_type;

	// Terrain generation methods
	static void		_generateIsland(int map[MAP_WIDTH][MAP_HEIGHT]);
	static void		_generateBasicIsland(int map[MAP_WIDTH][MAP_HEIGHT]);
	static void		_generateCrescentIsland(int map[MAP_WIDTH][MAP_HEIGHT]);
	static void		_generateLakeIsland(int map[MAP_WIDTH][MAP_HEIGHT]);
	static void		_generateArchipelago(int map[MAP_WIDTH][MAP_HEIGHT]);
	static void		_generateBeach(int map[MAP_WIDTH][MAP_HEIGHT], int islandType);
	static void		_generateDock(int map[MAP_WIDTH][MAP_HEIGHT]);

	// Terrain decoration generation methods
	static void		_generateTallGrass(Map *map);
	static void		_generateFlower(Map *map);
	static void		_generateDeepSea(Map *map);

	// Element generation methods
	static void		_generateCollectible(Map *map);

	// Generation Tools
	static void		_mappingLakes(int map[MAP_WIDTH][MAP_HEIGHT]);
	static int		_getSumLandSurfaces(int map[MAP_WIDTH][MAP_HEIGHT]);
	static t_veci	_findLandFromBorder(int map[MAP_WIDTH][MAP_HEIGHT], int side, int pos, int dir);

	// Map utilities
	static void		_clearMap(int map[MAP_WIDTH][MAP_HEIGHT]);
	static Tile		*_createTile(int tile);



	MapTools();
	MapTools(MapTools const &src);
	MapTools &operator=(MapTools const &rhs);

};

#endif