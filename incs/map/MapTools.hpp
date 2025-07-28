#ifndef MAPTOOLS_HPP
# define MAPTOOLS_HPP

# include "map/GameLife.hpp"
# include "map/Map.hpp"

class MapTools : public Map{
public:
	~MapTools();

	static Map	*generateMap();

private:
	MapTools();
	MapTools(MapTools const &src);
	MapTools &operator=(MapTools const &rhs);

};

#endif