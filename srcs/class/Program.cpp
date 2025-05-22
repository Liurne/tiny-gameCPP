#include "Program.hpp"

Program::Program() : MLXSetup(WIDTH, HEIGHT, false), display(0) {
	std::cout << "Program constructor called" << std::endl;
	nbGeneratedMap = 0;
	try {
		MLXSetup.init();
		renderer = MLXSetup.newImage(WIDTH, HEIGHT);
	}
	catch (const std::exception &e) {
		exit_error(e.what());
	}
	map.initView(MLXSetup);

	mapDisplay = (t_mapDisplay){.displayElement = true, .displayCollectible = true, .displayEnemy = true, .displaySpawn = true};

	fill_img(renderer, 0x000000FF);
	std::cout << "Map generated" << std::endl;
	map.generateMap();
}

Program::~Program() {
	std::cout << "Program destructor called" << std::endl;
}

void Program::run() {
	MLXSetup.imageToWindow(renderer, 0, 0);
	MLXSetup.keyHook(keyhook, this);
	MLXSetup.mouseHook(moosehook, this);
	MLXSetup.loopHook(process, this);
	MLXSetup.loop();
}

//Unused

Program::Program(Program const &src) : MLXSetup(WIDTH, HEIGHT, false) {
	std::cout << "Program copy constructor called" << std::endl;
	*this = src;
}

Program &Program::operator=(Program const &rhs) {
	std::cout << "Program assignment operator called" << std::endl;
	if (this != &rhs) {
		(void)rhs;
	}
	return (*this);
}

// Program process

void process(void *program) {
	Program		*prgm = static_cast<Program *>(program);
	// Map			*map = &prgm->map;
	(void)prgm;

	// displayMapImage(prgm->renderer, *map, &prgm->mapDisplay);
}

void keyhook(mlx_key_data_t keydata, void *program) {
	Program		*prgm = static_cast<Program *>(program);
	MLXWrapper	*mlx = &prgm->MLXSetup;
	Map			*map = &prgm->map;
	(void)map;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx->close();
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		mlx_image_to_png(prgm->renderer, "screenshot.png");
}

void moosehook(mouse_key_t button, action_t action, modifier_key_t mods, void* program) {
	// Program		*prgm = static_cast<Program *>(program);
	// t_veci pos = (t_veci){.x = 0, .y = 0};
	(void)button;
	(void)action;
	(void)mods;
	(void)program;

}