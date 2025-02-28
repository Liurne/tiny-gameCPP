#include "Program.hpp"

void process(void *program) {
	Program		*prgm = static_cast<Program *>(program);
	GameLife	*gameLife = &prgm->gameLife;
	Map			*map = &prgm->map;

	if (prgm->display == 0) {
		fill_img(prgm->renderer, 0x000000FF);
		gameLife->updateLife();
		gameLife->displayAliveCell(prgm->renderer);
	}
	if (prgm->display == 1) {
		map->displayMap(prgm->renderer);
	}
	if (prgm->display == 2) {
		fill_img(prgm->renderer, 0x3580C8FF);
		prgm->waveEquation.upadate();
		prgm->waveEquation.display(prgm->wave_img);
	}
}

void keyhook(mlx_key_data_t keydata, void *program) {
	Program		*prgm = static_cast<Program *>(program);
	MLXWrapper	*mlx = &prgm->MLXSetup;
	GameLife	*gameLife = &prgm->gameLife;
	Map			*map = &prgm->map;



	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx->close();
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
		// if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
			
	}
	if (prgm->display == 2) {
		if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
			prgm->waveEquation.drop((WIDTH / TILE_SIZE) / 2, (HEIGHT / TILE_SIZE) / 2, 10.0f);
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
			prgm->waveEquation.init();
	}
}