#include "../MLX/include/MLX42/MLX42.h"
// #include <cstdint>
#include <stdint.h>
#include <cmath>
#include <unistd.h>
#include <iostream>
#include "MLXWrapper.hpp"

#define WIDTH 512
#define HEIGHT 512

typedef union u_color {
	struct {
		uint8_t a;
		uint8_t b;
		uint8_t g;
		uint8_t	r;
	};
	uint32_t	raw;
}	t_color;

void rainbow(int32_t width, int32_t height, void *MLXSetup) {
	static_cast<MLXWrapper *>(MLXSetup)->resizeImage(0, width, height);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			t_color color = {.a = 0xFF, .b = 0x00, .g = 0x00, .r = 0x00};

			if (i + j <= (width + height) / 6 - 1) {
				const int min = 0;
				const int max = (width + height) / 6 - 1;

				color.r = 0xFF;
				color.g = (i + j - min) * 0xFF / (max - min);
				color.b = 0x00;
			}
			else if (i + j <= (width + height) / 6 * 2 - 1) {
				const int min = (width + height) / 6 - 1;
				const int max = (width + height) / 6 * 2 - 1;

				color.r = 0xFF - (i + j - min) * 0xFF / (max - min);
				color.g = 0xFF;
				color.b = 0x00;
			}
			else if (i + j <= (width + height) / 6 * 3 - 1) {
				const int min = (width + height) / 6 * 2 - 1;
				const int max = (width + height) / 6 * 3 - 1;

				color.r = 0x00;
				color.g = 0xFF;
				color.b = 0x00;
				color.b = (i + j - min) * 0xFF / (max - min);
			}
			else if (i + j <= (width + height) / 6 * 4 - 1) {
				const int min = (width + height) / 6 * 3 - 1;
				const int max = (width + height) / 6 * 4 - 1;

				color.r = 0x00;
				color.g = 0xFF - (i + j - min) * 0xFF / (max - min);
				color.b = 0xFF;
			}
			else if (i + j <= (width + height) / 6 * 5 - 1) {
				const int min = (width + height) / 6 * 4 - 1;
				const int max = (width + height) / 6 * 5 - 1;

				color.r = (i + j - min) * 0xFF / (max - min);
				color.g = 0x00;
				color.b = 0xFF;
			}
			else if (i + j <= (width + height) - 1) {
				const int min = (width + height) / 6 * 5 - 1;
				const int max = (width + height) - 1;

				color.r = 0xFF;
				color.g = 0x00;
				color.b = 0xFF - (i + j - min) * 0xFF / (max - min);
			}
			// diagonal guide
			 if (i + j == (width + height) / 6 - 1 || i + j == (width + height) / 6 * 2 - 1 || i + j == (width + height) / 6 * 3 - 1
				|| i + j == (width + height) / 6 * 4 - 1 || i + j == (width + height) / 6 * 5 - 1)
				color = (t_color){.a = 0xFF, .b = 0x00, .g = 0x00, .r = 0x00};
			// // horizontal guide
			if (i == (width + height) / 6 || i == (width + height) / 6 * 2 || i == (width + height) / 6 * 3
				|| i == (width + height) / 6 * 4 || i == (width + height) / 6 * 5)
				color = (t_color){.a = 0xFF, .b = 0x00, .g = 0x00, .r = 0x00};
			if (j == (width + height) / 6 || j == (width + height) / 6 * 2 || j == (width + height) / 6 * 3
				|| j == (width + height) / 6 * 4 || j == (width + height) / 6 * 5)
				color = (t_color){.a = 0xFF, .b = 0x00, .g = 0x00, .r = 0x00};
			static_cast<MLXWrapper *>(MLXSetup)->putPixel(0, i, j, color.raw);
		}
	}
	static_cast<MLXWrapper *>(MLXSetup)->imageToWindow(0, 0, 0);
}

void my_hook(void *MLXSetup) {
	if (static_cast<MLXWrapper *>(MLXSetup)->isKeyDown(MLX_KEY_ESCAPE))
		mlx_close_window(static_cast<MLXWrapper *>(MLXSetup)->getMlx());
	if (static_cast<MLXWrapper *>(MLXSetup)->isKeyDown(MLX_KEY_W))
		static_cast<MLXWrapper *>(MLXSetup)->getImage(1)->instances[0].y -= 5;
	if (static_cast<MLXWrapper *>(MLXSetup)->isKeyDown(MLX_KEY_S))
		static_cast<MLXWrapper *>(MLXSetup)->getImage(1)->instances[0].y += 5;
	if (static_cast<MLXWrapper *>(MLXSetup)->isKeyDown(MLX_KEY_D))
		static_cast<MLXWrapper *>(MLXSetup)->getImage(1)->instances[0].x += 5;
	if (static_cast<MLXWrapper *>(MLXSetup)->isKeyDown(MLX_KEY_A))
		static_cast<MLXWrapper *>(MLXSetup)->getImage(1)->instances[0].x -= 5;
	(void)MLXSetup;
}

int main() {
	std::cout << "Welcome in fract-ol CPP working with MLX42" << std::endl;

	MLXWrapper	MLXSetup(WIDTH, HEIGHT, true);

	try {
		MLXSetup.init();
		MLXSetup.newImage(WIDTH, HEIGHT);
		MLXSetup.newImage(WIDTH, HEIGHT);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return (-1);
	}

	for (int i = 0; i < WIDTH / 10; ++i)
		for (int j = 0; j < HEIGHT / 10; ++j)
			MLXSetup.putPixel(1, i , j, (t_color){.a = 0xFF, .b = 0xFF, .g = 0xFF, .r = 0xFF}.raw);

	rainbow(MLXSetup.getMlx()->width, MLXSetup.getMlx()->height, MLXSetup());

	MLXSetup.imageToWindow(0, 0, 0);
	MLXSetup.imageToWindow(1, WIDTH / 2 - (MLXSetup.getImage(1)->width / 2) - 1, HEIGHT / 2 - (MLXSetup.getImage(1)->height / 2) - 1);

	MLXSetup.resizeHook(rainbow, MLXSetup());

	MLXSetup.loopHook(my_hook, MLXSetup());
	MLXSetup.loop();
	// mlx_delete_image(MLXSetup.getMlx(), mlxData.image);
	// mlx_terminate(MLXSetup.getMlx());
}