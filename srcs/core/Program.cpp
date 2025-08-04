#include "core/Program.hpp"

Program::Program() : MLXSetup(WIN_WIDTH, WIN_HEIGHT, false) {
	try {
		MLXSetup.init();
		renderer = MLXSetup.newImage(WIN_WIDTH, WIN_HEIGHT);
		mapView = MLXSetup.newImage(MAP_WIDTH * TEXTURE_SIZE, MAP_HEIGHT * TEXTURE_SIZE);
		mapPreview = MLXSetup.newImage(MAP_WIDTH * MAP_TILE_SIZE, MAP_HEIGHT * MAP_TILE_SIZE);
		playerView = MLXSetup.newImage(TEXTURE_SIZE, TEXTURE_SIZE);
	}
	catch (const std::exception &e) {
		exit_error(e.what());
	}

	map = NULL;

	fill_img(renderer, DEEP_WATER_COLOR);
	fill_img(playerView, 0xFF000099);
}

Program::Program(int run_mode) : MLXSetup(WIN_WIDTH, WIN_HEIGHT, false), runMode(run_mode) {
	try {
		MLXSetup.init();
		renderer = MLXSetup.newImage(WIN_WIDTH, WIN_HEIGHT);
		mapView = MLXSetup.newImage(MAP_WIDTH * TEXTURE_SIZE, MAP_HEIGHT * TEXTURE_SIZE);
		mapPreview = MLXSetup.newImage(MAP_WIDTH * MAP_TILE_SIZE, MAP_HEIGHT * MAP_TILE_SIZE);
		playerView = MLXSetup.newImage(PLAYER_SIZE, PLAYER_SIZE);
	}
	catch (const std::exception &e) {
		exit_error(e.what());
	}

	map = NULL;

	fill_img(renderer, DEEP_WATER_COLOR);
	fill_img(playerView, 0xFF000099);
}

Program::~Program() {
	if (renderer) {
		mlx_delete_image(MLXSetup.getMlx(), renderer);
	}
	if (map) {
		delete map;
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
}

void Program::run() {
	MLXSetup.imageToWindow(renderer, 0, 0);
	if (runMode == 1) {
		std::cout << "Running in debug mode" << std::endl;
		MLXSetup.imageToWindow(mapPreview, 0, 0);
	}
	if (runMode == 0) {
		std::cout << "Running in release mode" << std::endl;
		MLXSetup.imageToWindow(mapView, WIN_WIDTH * 0.5 - (MAP_WIDTH * TEXTURE_SIZE * 0.5), WIN_HEIGHT * 0.5 - (MAP_HEIGHT * TEXTURE_SIZE * 0.5));
		MLXSetup.imageToWindow(playerView, WIN_WIDTH * 0.5 - (TEXTURE_SIZE * 0.5), WIN_HEIGHT * 0.5 - (TEXTURE_SIZE * 0.5));
	}

	MLXSetup.keyHook(keyhook, this);
	MLXSetup.mouseHook(moosehook, this);
	MLXSetup.loopHook(process, this);
	MLXSetup.loop();
}

//Unused

Program::Program(Program const &src) : MLXSetup(WIN_WIDTH, WIN_HEIGHT, false) {
	*this = src;
}

Program &Program::operator=(Program const &rhs) {
	if (this != &rhs) {
		(void)rhs;
	}
	return (*this);
}

// Program process

void process(void *program) {
	Program		*prgm = static_cast<Program *>(program);
	Keyboard	*keyboard = &prgm->keyboard;
	MLXWrapper	*mlx = &prgm->MLXSetup;
	Map			*map = prgm->map;

	//Basic actions
	if (keyboard->isActionActive(KEY_QUIT)) {
		mlx->close();
	}
	if (prgm->keyboard.isActionActive(KEY_SCREENSHOT)) {
		mlx_image_to_png(prgm->renderer, "screenshot.png");
	}
	if (prgm->keyboard.isActionActive(KEY_GENERATE_MAP)) {
		if (map) {
			delete map;
		}
		map = MapTools::generateMap();
		MapTools::generateView(map, prgm->renderer);
	}

	//Player movement
	if (prgm->keyboard.isActionActive(KEY_UP)) {
		prgm->playerView->instances[0].y -= 5;
	}
	if (prgm->keyboard.isActionActive(KEY_DOWN)) {
		prgm->playerView->instances[0].y += 5;
	}
	if (prgm->keyboard.isActionActive(KEY_LEFT)) {
		prgm->playerView->instances[0].x -= 5;
	}
	if (prgm->keyboard.isActionActive(KEY_RIGHT)) {
		prgm->playerView->instances[0].x += 5;
	}
	//displayMapPreview(prgm->renderer, *map);
}

void keyhook(mlx_key_data_t keydata, void *program) {
	Program		*prgm = static_cast<Program *>(program);

	prgm->keyboard.update(keydata);
}

void moosehook(mouse_key_t button, action_t action, modifier_key_t mods, void *program) {
	// Program		*prgm = static_cast<Program *>(program);
	// t_veci pos = (t_veci){.x = 0, .y = 0};
	(void)button;
	(void)action;
	(void)mods;
	(void)program;

}