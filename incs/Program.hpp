#ifndef PROGRAM_HPP
# define PROGRAM_HPP

# include "include.h"
# include "error.h"
# include "game_rule.h"
# include "MLXWrapper.hpp"
# include "GameLife.hpp"
# include "Map.hpp"
# include "MapVisualGenerator.hpp"
# include "WaveEquation.hpp"

class Program {
public:
	Program();
	~Program();

	int nbGeneratedMap;

	void		run();

	MLXWrapper	MLXSetup;
	mlx_image_t	*renderer;

	Map map;
	t_mapDisplay mapDisplay;

	int display;

private:
	Program(Program const &src);
	Program &operator=(Program const &rhs);



};

#endif