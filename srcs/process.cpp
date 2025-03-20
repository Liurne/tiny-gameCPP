#include "Program.hpp"

void process(void *program) {
	Program		*prgm = static_cast<Program *>(program);
	GameLife	*gameLife = &prgm->gameLife;
	Map			*map = &prgm->map;

	if (prgm->display == 0) {
		fill_img(prgm->renderer, 0x000000FF);
		gameLife->updateLife();
		gameLife->displayAliveCell(prgm->renderer, TILE_SIZE);
	}
	if (prgm->display == 1) {
		map->displayMap(prgm->renderer);
	}
	if (prgm->display == 2) {
		fill_img(prgm->renderer, 0x3580C8FF);
		prgm->waveEquation.upadate();
		prgm->waveEquation.display(prgm->renderer);
	}
}

void keyhook(mlx_key_data_t keydata, void *program) {
	Program		*prgm = static_cast<Program *>(program);
	MLXWrapper	*mlx = &prgm->MLXSetup;
	GameLife	*gameLife = &prgm->gameLife;
	Map			*map = &prgm->map;


	std::cout << "key: " << keydata.key << std::endl;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx->close();
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		mlx_image_to_png(prgm->renderer, "screenshot.png");
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		prgm->display = 0;
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		prgm->display = 1;
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		prgm->display = 2;
	if (prgm->display == 0) {
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			gameLife->generateGrid();
	}
	if (prgm->display == 1) {
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			map->initMap();
		if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
			map->createMapImage(prgm->map_img, TILE_SIZE);
			
	}
	if (prgm->display == 2) {
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			prgm->waveEquation.drop((WIDTH / TILE_SIZE) / 2, (HEIGHT / TILE_SIZE) / 2, 10.0f);
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
			prgm->waveEquation.init();
	}
}

void moosehook(mouse_key_t button, action_t action, modifier_key_t mods, void* program) {
	Program		*prgm = static_cast<Program *>(program);
	t_veci pos = (t_veci){.x = 0, .y = 0};
	(void)mods;

	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS) {
		mlx_get_mouse_pos(prgm->MLXSetup.getMlx(), &pos.x, &pos.y);
		if (prgm->display == 2)
			prgm->waveEquation.drop(pos.x / TILE_SIZE, pos.y / TILE_SIZE, 10.0f);
		std::cout << "(" << pos.x << ", " << pos.y << ")" << std::endl;
	}
}