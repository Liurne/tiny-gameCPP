#include "Program.hpp"

Program::Program() : MLXSetup(WIDTH, HEIGHT, false) {
	std::cout << "Program constructor called" << std::endl;
	try {
		MLXSetup.init();
		renderer = MLXSetup.newImage(WIDTH, HEIGHT);
	}
	catch (const std::exception &e) {
		exit_error(e.what());
	}
	map.initView(MLXSetup);

	fill_img(renderer, DEEP_WATER_COLOR);
	std::cout << "Map generated" << std::endl;
	map.generateMap();
}

Program::~Program() {
	if (renderer) {
		mlx_delete_image(MLXSetup.getMlx(), renderer);
	}
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
	Map			*map = &prgm->map;

	displayMapPreview(prgm->renderer, *map);
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
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS) {
		map->generateMap();
	}
}

void moosehook(mouse_key_t button, action_t action, modifier_key_t mods, void* program) {
	// Program		*prgm = static_cast<Program *>(program);
	// t_veci pos = (t_veci){.x = 0, .y = 0};
	(void)button;
	(void)action;
	(void)mods;
	(void)program;

}