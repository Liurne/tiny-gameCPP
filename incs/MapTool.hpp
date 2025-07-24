#ifndef MAPTOOL_HPP
# define MAPTOOL_HPP

#include "GameLife.hpp"
#include "Map.hpp"

class MapGenerator {
public:
	MapGenerator();
	~MapGenerator();

	static Map	generateMap();

private:

};

#endif