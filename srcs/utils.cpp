#include "Program.hpp"

void exit_error(const std::string &msg) {
	std::cerr << "Error: " << msg << std::endl;
	exit(1);
}

void my_keyhook(void *program) {
	Program *prgm = static_cast<Program *>(program);
	MLXWrapper *mlx = &prgm->MLXSetup;
	GameLife *game = &prgm->gameLife;

	std::cerr << "my_hook called" << std::endl;

	if (mlx->isKeyDown(MLX_KEY_ESCAPE))
		mlx->close();
	if (mlx->isKeyDown(MLX_KEY_SPACE))
		game->generateGrid();
	if (mlx->isKeyDown(MLX_KEY_ENTER)) {
		std::cerr << "Enter key pressed" << std::endl;
		mlx->imageToWindow(prgm->test, 0, 0);

	}
	std::cerr << "my_hook exit" << std::endl;
}

void my_program(void *program) {
	Program *prgm = static_cast<Program *>(program);
	MLXWrapper *mlx = &prgm->MLXSetup;
	GameLife *game = &prgm->gameLife;

	std::cerr << "my_program called" << std::endl;

	// game->updateLife();
	game->displayAliveCell(mlx, prgm->cell);
	// mlx->imageToWindow(prgm->test, 0, 0);
	// mlx->imageToWindow(prgm->renderer, 0, 0);
	std::cerr << "my_program exit" << std::endl;
}

void put_pixel(mlx_image_t *img, int32_t x, int32_t y, uint32_t color) {
	mlx_put_pixel(img, x, y, color);
}

void fill_img(mlx_image_t *img, uint32_t color, int32_t width, int32_t height) {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			put_pixel(img, i, j, color);
		}
	}
}

bool resize_image(mlx_image_t *img, int32_t nwidth, int32_t nheight) {
	const bool	resized = mlx_resize_image(img, nwidth, nheight);
	if (!resized)
		throw std::runtime_error(ERR_MLX_RESIZE_IMAGE);
	return (resized);
}

void gradiant(mlx_image *img, int32_t width, int32_t height) {
	
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			t_color color = {.a = 0xFF, .b = 0xFF, .g = 0x88, .r = 0x00};
			color.b = (0xFF * (static_cast<float>(i + j) / (width + height)));
			put_pixel(img, i, j, color.raw);
		}
	}
}