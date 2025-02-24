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

#endif