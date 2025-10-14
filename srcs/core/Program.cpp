#include "core/Program.hpp"

Program::Program() : MLXSetup(WIN_WIDTH, WIN_HEIGHT, false), runMode(0) {
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

	player = new Player(0, 0, 0, &keyboard);
	player->setView(playerView);

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

	player = new Player(0, 0, 0, &keyboard);
	player->setView(playerView);

	fill_img(playerView, 0xFF000099);
}

Program::~Program() {
	if (renderer) {
		mlx_delete_image(MLXSetup.getMlx(), renderer);
	}
	if (map) {
		delete map;
	}
	if (player) {
		delete player;
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

		map = MapTools::generateMap();
		MapTools::generateView(map, renderer);

		player->setPosition(map->getStart().x * TILE_SIZE, map->getStart().y * TILE_SIZE);
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
	Player		*player = prgm->player;


	//Basic actions
	if (keyboard->isActionActive(KEY_QUIT)) {
		mlx->close();
	}
	if (prgm->keyboard.isActionActive(KEY_SCREENSHOT)) {
		mlx_image_to_png(prgm->renderer, "screenshot.png");
	}
	if (prgm->keyboard.isActionActive(KEY_GENERATE_MAP)) {
		if (prgm->map) {
			std::cout << "me" << std::endl;
			delete prgm->map;
			prgm->map = NULL;
			std::cout << "meme" << std::endl;
		}
		std::cout << "ok" << std::endl;
		prgm->map = MapTools::generateMap();
		MapTools::generateView(prgm->map, prgm->renderer);
		player->setPosition(prgm->map->getStart().x * TILE_SIZE, prgm->map->getStart().y * TILE_SIZE);

	}
<<<<<<< HEAD
	player->update(map);
=======
	player->update(prgm->map);
	// std::cout << "Player position: (" << player->getPosition().x << ", " << player->getPosition().y << ")" << std::endl;
	// //Player movement
	// if (prgm->keyboard.isActionActive(KEY_UP)) {
	// 	prgm->playerView->instances[0].y -= 5;
	// }
	// if (prgm->keyboard.isActionActive(KEY_DOWN)) {
	// 	prgm->playerView->instances[0].y += 5;
	// }
	// if (prgm->keyboard.isActionActive(KEY_LEFT)) {
	// 	prgm->playerView->instances[0].x -= 5;
	// }
	// if (prgm->keyboard.isActionActive(KEY_RIGHT)) {
	// 	prgm->playerView->instances[0].x += 5;
	// }
>>>>>>> a3355394f8159da3f124ebd4d12f490ca646eb48
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