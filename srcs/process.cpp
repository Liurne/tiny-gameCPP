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
		std::cout << "Enter Map Density: ";
		prgm->isWritingIsleDensity = true;
	}
	if (keydata.key == MLX_KEY_G && keydata.action == MLX_PRESS && !prgm->isWritingIsleDensity) {
		std::cout << "Enter Grass Density: ";
		prgm->isWritingGrassDensity = true;
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS && (prgm->isWritingIsleDensity || prgm->isWritingGrassDensity)) {
		float num;
		std::stringstream ss(prgm->density);
    	ss >> num;
		if (num > 1.0f)
			prgm->density = "0.55";
		if (prgm->isWritingIsleDensity) {
			std::cout << "Map Density: " << prgm->density << std::endl;
			map->generateMap(num);
			std::cout << "Map Generated" << std::endl;
			prgm->isWritingIsleDensity = false;
		}
		if (prgm->isWritingGrassDensity) {
			std::cout << "Grass Density: " << prgm->density << std::endl;
			map->generateMapGrass(num);
			map->generateMapGrassBig(num);
			std::cout << "Grass Generated" << std::endl;
			prgm->isWritingGrassDensity = false;
		}
		prgm->density = "";
	}
	if (prgm->isWritingIsleDensity || prgm->isWritingGrassDensity) {
		if (keydata.key == MLX_KEY_BACKSPACE && keydata.action == MLX_PRESS) {
			if (!density.empty()) {
				density.resize(density.size() - 1);  // Resize the string to remove the last character
			}
		}
		else if (keydata.key >= MLX_KEY_KP_0 && keydata.key <= MLX_KEY_KP_9 && keydata.action == MLX_PRESS) {
			prgm->density += '0' + (keydata.key - MLX_KEY_KP_0);
		}
		else if (keydata.key == MLX_KEY_KP_DECIMAL && keydata.action == MLX_PRESS) {
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