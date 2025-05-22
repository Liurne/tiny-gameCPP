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

	void 		init();
	void		run();

	MLXWrapper	MLXSetup;
	mlx_image_t	*renderer;

	Map map;

	mlx_image_t	*mapView;
	mlx_image_t	*mapPreview;
	mlx_image_t	*playerView;

private:
	Program(Program const &src);
	Program &operator=(Program const &rhs);
};

void process(void *program);
void keyhook(mlx_key_data_t keydata, void *program);
void moosehook(mouse_key_t button, action_t action, modifier_key_t mods, void* param);

#endif