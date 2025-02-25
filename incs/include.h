#ifndef INCLUDE_H
# define INCLUDE_H

# include <iostream>
# include <unistd.h>
# include <stdint.h>
# include <stdint.h>
# include <vector>
# include <cmath>

# include "../MLX/include/MLX42/MLX42.h"

typedef union u_color {
	struct {
		uint8_t a;
		uint8_t b;
		uint8_t g;
		uint8_t	r;
	};
	uint32_t	raw;
}	t_color;

void exit_error(const std::string &msg);
void my_keyhook(void *program);
void my_program(void *program);
void put_pixel(mlx_image_t *img, int32_t x, int32_t y, uint32_t color);
void fill_img(mlx_image_t *img, uint32_t color, int32_t width, int32_t height);
bool resize_image(mlx_image_t *img, int32_t nwidth, int32_t nheight);
void gradiant(mlx_image *img, int32_t width, int32_t height);


#endif