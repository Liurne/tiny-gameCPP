#ifndef PROGRAM_HPP
# define PROGRAM_HPP

# include "include.h"
# include "error.h"
# include "game_rule.h"
# include "MLXWrapper.hpp"
# include "GameLife.hpp"

class Program {
public:
	Program();
	~Program();

	void		run();
	
	MLXWrapper	MLXSetup;
	mlx_image_t	*renderer;
	mlx_image_t	*test;

	GameLife	gameLife;
	mlx_image_t	*cell;

private:
	Program(Program const &src);
	Program &operator=(Program const &rhs);

};

#endif