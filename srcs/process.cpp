#include "Program.hpp"

void process(void *program) {
	Program *prgm = static_cast<Program *>(program);
	GameLife *game = &prgm->gameLife;

	prgm->iter++;
	if (prgm->iter % 10 == 0)
		game->generateGrid();
	game->updateLife();

	fill_img(prgm->renderer, 0x00000000);
	game->displayAliveCell(prgm->renderer, prgm->cell);
}

void keyhook(mlx_key_data_t keydata, void *program) {
	Program *prgm = static_cast<Program *>(program);
	MLXWrapper *mlx = &prgm->MLXSetup;
	GameLife *game = &prgm->gameLife;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx->close();
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		game->generateGrid();
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
		game->updateLife();
}