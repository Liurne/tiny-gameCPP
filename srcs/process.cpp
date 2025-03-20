#include "Program.hpp"

void process(void *program) {
	Program		*prgm = static_cast<Program *>(program);
	Map			*map = &prgm->map;

	displayMapImage(prgm->renderer, *map, &prgm->mapDisplay);
}

void keyhook(mlx_key_data_t keydata, void *program) {
	Program		*prgm = static_cast<Program *>(program);
	MLXWrapper	*mlx = &prgm->MLXSetup;
	Map			*map = &prgm->map;
	t_mapDisplay *mapDisplay = &prgm->mapDisplay;
	std::string density;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx->close();
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		mlx_image_to_png(prgm->renderer, "screenshot.png");
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		mapDisplay->displayMapGrassBig = 0;
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		mapDisplay->displayMapGrassBig = 1;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS) {
		map->generateMap();
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && !prgm->isWritingGrassDensity) {
		prgm->isWritingIsleDensity = true;
	}
	if (keydata.key == MLX_KEY_G && keydata.action == MLX_PRESS && !prgm->isWritingIsleDensity) {
		prgm->isWritingGrassDensity = true;
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS) {
		float num;
		std::stringstream ss(prgm->density);
    	ss >> num;
		if (num > 1.0f)
			prgm->density = "1.0";
		if (prgm->isWritingIsleDensity) {
			map->generateMap(num);
			prgm->isWritingIsleDensity = false;
		}
		if (prgm->isWritingGrassDensity) {
			map->generateMapGrass(num);
			prgm->isWritingGrassDensity = false;
		}
		prgm->density = "";
	}
	if (prgm->isWritingIsleDensity || prgm->isWritingGrassDensity) {
		if (keydata.key == MLX_KEY_BACKSPACE && keydata.action == MLX_PRESS) {
			if (prgm->density.size() > 0)
				prgm->density.pop_back();
		}
		else if (keydata.key >= MLX_KEY_0 && keydata.key <= MLX_KEY_9 && keydata.action == MLX_PRESS) {
			prgm->density += keydata.key;
		}
		else if (keydata.key == MLX_KEY_PERIOD && keydata.action == MLX_PRESS) {
			prgm->density += '.';
		}
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