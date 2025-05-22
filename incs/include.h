#ifndef INCLUDE_H
# define INCLUDE_H

# include <iostream>
# include <string>
# include <sstream>
# include <unistd.h>
# include <stdint.h>
# include <stdint.h>
# include <vector>
# include <cmath>
# include <ctime>

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

typedef struct u_veci {
	int x;
	int y;
}	t_veci;

typedef struct u_rect {
	t_veci pos;
	int width;
	int height;
}	t_rect;

typedef std::vector<int> t_vectori;

void exit_error(const std::string &msg);
void put_pixel(mlx_image_t *img, int32_t x, int32_t y, uint32_t color);
void fill_img(mlx_image_t *img, uint32_t color);
void put_img_to_img(mlx_image_t *img1, mlx_image_t *img2, t_rect *src, t_rect *dst);
void draw_rect(mlx_image_t *img, int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color);
bool resize_image(mlx_image_t *img, int32_t nwidth, int32_t nheight);
void gradiant(mlx_image_t *img, int32_t width, int32_t height);

void process(void *program);
void keyhook(mlx_key_data_t keydata, void *program);
void moosehook(mouse_key_t button, action_t action, modifier_key_t mods, void* param);

#endif