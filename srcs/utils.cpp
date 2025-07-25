#include "Program.hpp"

void exit_error(const std::string &msg) {
	std::cerr << "Error: " << msg << std::endl;
	exit(1);
}

void put_pixel(mlx_image_t *img, int32_t x, int32_t y, uint32_t color) {
	mlx_put_pixel(img, x, y, color);
}

uint32_t get_pixel(mlx_image_t *img, uint32_t x, uint32_t y) {
    if (x >= img->width || y >= img->height) {
        throw std::runtime_error(ERR_MLX_PIXEL_INDEX);
    }

    uint8_t *pixel = &img->pixels[(y * img->width + x) * sizeof(int32_t)];

    uint32_t color = 0;
    color |= (uint32_t)*(pixel++) << 24;  // Alpha channel
    color |= (uint32_t)*(pixel++) << 16;  // Red channel
    color |= (uint32_t)*(pixel++) << 8;   // Green channel
    color |= (uint32_t)*(pixel);          // Blue channel

    return color;
}

t_color get_color(uint32_t color)
{
	return ((t_color){.a = (uint8_t)(color & 0xFF), .b = (uint8_t)((color >> 8) & 0xFF), .g = (uint8_t)((color >> 16) & 0xFF), .r = (uint8_t)((color >> 24) & 0xFF)});
}

void fill_img(mlx_image_t *img, uint32_t color) {
	for (uint32_t i = 0; i < img->width; ++i) {
		for (uint32_t j = 0; j < img->height; ++j) {
			put_pixel(img, i, j, color);
		}
	}
}

void	put_img_to_img(mlx_image_t *img1, mlx_image_t *img2, t_rect *src, t_rect *dst)
{
	int	i;
	int	j;
	int	tmp_x;
	int	tmp_y;

	i = 0;
	while (i < dst->width)
	{
		j = 0;
		tmp_x = src->pos.x + (i * src->width) / dst->width;
		while (j < dst->height)
		{
			tmp_y = src->pos.y + (j * src->height) / dst->height;
			put_pixel(img1, i + dst->pos.x, j + dst->pos.y,
				get_pixel(img2, tmp_x, tmp_y));
			j++;
		}
		i++;
	}
}

void draw_rect(mlx_image_t *img, int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color) {
	for (int32_t i = 0; i < width; ++i) {
		for (int32_t j = 0; j < height; ++j) {
			put_pixel(img, x + i, y + j, color);
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