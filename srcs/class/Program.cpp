#include "Program.hpp"

Program::Program() : MLXSetup(WIDTH, HEIGHT, false) {
	std::cout << "Program constructor called" << std::endl;
	try {
		MLXSetup.init();
		renderer = MLXSetup.newImage(WIDTH, HEIGHT);
		mapView = MLXSetup.newImage(MAP_WIDTH * TEXTURE_SIZE, MAP_HEIGHT * TEXTURE_SIZE);
		mapPreview = MLXSetup.newImage(MAP_WIDTH * MAP_TILE_SIZE, MAP_HEIGHT * MAP_TILE_SIZE);
		playerView = MLXSetup.newImage(TEXTURE_SIZE, TEXTURE_SIZE);
	}
	catch (const std::exception &e) {
		exit_error(e.what());
	}
	map.setView(mapView, mapPreview);

	fill_img(renderer, DEEP_WATER_COLOR);
	fill_img(playerView, 0xFF000099);
	map.generateMap();
}

Program::~Program() {
	if (renderer) {
		mlx_delete_image(MLXSetup.getMlx(), renderer);
	}
	if (mapView) {
		mlx_delete_image(MLXSetup.getMlx(), mapView);
	}
	if (mapPreview) {
		mlx_delete_image(MLXSetup.getMlx(), mapPreview);
	}
	if (playerView) {
		mlx_delete_image(MLXSetup.getMlx(), playerView);
	}
	std::cout << "Program destructor called" << std::endl;
}

void Program::run() {
	MLXSetup.imageToWindow(renderer, 0, 0);
	MLXSetup.imageToWindow(playerView, WIDTH * 0.5 - (TEXTURE_SIZE * 0.5), HEIGHT * 0.5 - (TEXTURE_SIZE * 0.5));
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
	// put_img_to_img(prgm->renderer, prgm->mapView, NULL, NULL);
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
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) {
		prgm->playerView->instances[0].y -= 5;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS) {
		prgm->playerView->instances[0].y += 5;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS) {
		prgm->playerView->instances[0].x -= 5;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS) {
		prgm->playerView->instances[0].x += 5;
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