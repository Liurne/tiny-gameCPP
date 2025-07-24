#include "Program.hpp"

void process(void *program) {
	Program		*prgm = static_cast<Program *>(program);
	(void)prgm; // To avoid unused variable warning
}

void keyhook(mlx_key_data_t keydata, void *program) {
	Program		*prgm = static_cast<Program *>(program);
	MLXWrapper	*mlx = &prgm->MLXSetup;
	GameLife	*gol = &prgm->gameLife;


	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx->close();
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS) {
		gol->updateLife();
		fill_img(prgm->renderer, 0x000000FF);
		gol->displayAliveCell(prgm->renderer, TILE_SIZE);
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS) {
		gol->generateGrid(GRID_WIDTH, GRID_HEIGHT, GRID_DENSITY);
		// gol->generateFragGrid(GRID_WIDTH, GRID_HEIGHT, 0.45f, 0.5f);
		fill_img(prgm->renderer, 0x000000FF);
		gol->displayAliveCell(prgm->renderer, TILE_SIZE);
		prgm->nbGeneratedGrids++;
		std::cout << "Gol generated: " << prgm->nbGeneratedGrids << std::endl;
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