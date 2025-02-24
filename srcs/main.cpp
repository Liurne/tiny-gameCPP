#include "MLXWrapper.hpp"
#include "game_rule.h"

void exit_error(const std::string &msg) {
	std::cerr << "Error: " << msg << std::endl;
	exit(1);
}

void my_hook(void *MLXSetup) {
	if (static_cast<MLXWrapper *>(MLXSetup)->isKeyDown(MLX_KEY_ESCAPE))
		mlx_close_window(static_cast<MLXWrapper *>(MLXSetup)->getMlx());
}

void put_pixel(mlx_image_t *img, int32_t x, int32_t y, uint32_t color) {
	mlx_put_pixel(img, x, y, color);
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

int main(int ac, char **av) {
	std::cout << "Welcome in tiny-game CPP working with MLX42" << std::endl;
	if (!ac)
		exit_error(ERR_ARGS);
	std::cout << "You entered: " << av[0] << std::endl;

	MLXWrapper MLXSetup (WIDTH, HEIGHT, true);
	mlx_image_t *renderer;
	mlx_image_t *image;

	try {
		MLXSetup.init();
		renderer = MLXSetup.newImage(WIDTH/2, HEIGHT/2);
		image = MLXSetup.newTexture("./assets/catmeme.png");
		resize_image(image, 128, 128);
	}
	catch (const std::exception &e) {
		exit_error(e.what());
	}

	gradiant(renderer, WIDTH/2, HEIGHT/2);
	MLXSetup.imageToWindow(renderer, 0, 0);
	MLXSetup.imageToWindow(renderer, WIDTH/2, HEIGHT/2);
	MLXSetup.imageToWindow(renderer, 0, HEIGHT/2);
	MLXSetup.imageToWindow(renderer, WIDTH/2, 0);
	MLXSetup.imageToWindow(image, 0, 0);

	MLXSetup.loopHook(my_hook, &MLXSetup);
	MLXSetup.loop();
	return (0);
}