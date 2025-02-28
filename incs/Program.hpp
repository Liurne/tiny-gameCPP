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

	GameLife	gameLife;

	Map map;
	mlx_image_t	*map_img;

	WaveEquation waveEquation;
	mlx_image_t	*wave_img;


	int display;

private:
	Program(Program const &src);
	Program &operator=(Program const &rhs);

};

#endif