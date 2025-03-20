#ifndef PROGRAM_HPP
# define PROGRAM_HPP

# include "include.h"
# include "error.h"
# include "game_rule.h"
# include "MLXWrapper.hpp"
# include "GameLife.hpp"
# include "Map.hpp"
# include "WaveEquation.hpp"

class Program {
public:
	Program();
	~Program();

	void		run();
	
	MLXWrapper	MLXSetup;
	mlx_image_t	*renderer;

	Map map;
	t_mapDisplay mapDisplay;

	int display;
	bool isWritingIsleDensity;
	bool isWritingGrassDensity;
	std::string density;


private:
	Program(Program const &src);
	Program &operator=(Program const &rhs);



};

#endif