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

	int nbGeneratedGrids;

	void		run();

	MLXWrapper	MLXSetup;
	mlx_image_t	*renderer;

	GameLife	gameLife;

private:
	Program(Program const &src);
	Program &operator=(Program const &rhs);



};

#endif