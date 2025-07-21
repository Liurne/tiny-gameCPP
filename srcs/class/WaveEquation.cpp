#include "WaveEquation.hpp"

//Public

WaveEquation::WaveEquation() : width(WIDTH/TILE_SIZE), height(HEIGHT/TILE_SIZE) {
	for (int i = 0; i < width; i++) {
		std::vector<float> row;
		for (int j = 0; j < height; j++) {
			row.push_back(0.0f);
		}
		grid.push_back(row);
	}
	old_grid = grid;
}

WaveEquation::~WaveEquation() {

}

void WaveEquation::init() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			grid[i][j] = 0.0f;
			old_grid[i][j] = 0.0f;
		}
	}
}

// void update() {
//     std::vector<std::vector<float>> new_grid = grid;

//     for (int x = 1; x < WIDTH - 1; ++x) {
//         for (int y = 1; y < HEIGHT - 1; ++y) {
//             float laplacian = grid[x + 1][y] + grid[x - 1][y] + grid[x][y + 1] + grid[x][y - 1] - 4 * grid[x][y];
//             new_grid[x][y] = 2 * grid[x][y] - old_grid[x][y] + c * c * dt * dt * laplacian;
//             new_grid[x][y] *= damping;
//         }
//     }

//     old_grid = grid;
//     grid = new_grid;
// }

void WaveEquation::upadate() {
	std::vector<std::vector<float> > new_grid = grid;

	for (int x = 1; x < width - 1; ++x) {
		for (int y = 1; y < height - 1; ++y) {
			float laplacian = grid[x + 1][y] + grid[x - 1][y] + grid[x][y + 1] + grid[x][y - 1] - 4 * grid[x][y];
			new_grid[x][y] = 2 * grid[x][y] - old_grid[x][y] + c * c * dt * dt * laplacian;
			new_grid[x][y] *= damping;

			float energy = std::abs(grid[x][y]);
			float non_linear_damping = 1.0f / (1.0f + energy * energy * 0.001f);
			new_grid[x][y] *= non_linear_damping;

			if (x == 1 || x == width - 2 || y == 1 || y == height - 2) {
				new_grid[x][y] = new_grid[x][y] * -0.3f;
				new_grid[x][y] *= 0.9f;
			}
		}
	}

	old_grid = grid;
	grid = new_grid;
}

void WaveEquation::drop(int x, int y, float amplitude) {
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;
	grid[x][y] = amplitude;
}

void WaveEquation::display(mlx_image_t *renderer) {
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			float height = grid[x][y];
			float color = (height + 1.0f) * 127.5f;
			// t_color waveColor = (t_color){.a = 255, .b = (uint8_t)(255 - color * 0.5f), .g = (uint8_t)color, .r = (uint8_t)(100 + color * 0.5f)};
			t_color waveColor = (t_color){.a = (uint8_t)color, .b = 255, .g = 255, .r = 255};

			float speed = std::abs(grid[x][y] - old_grid[x][y]);
			if (speed > 0.2f) {
				waveColor.a = 255;
			}

			if (grid[x][y] == 0.0f || !grid[x][y]) {
				waveColor.a = 255;
				waveColor.b = 200;
				waveColor.g = 128;
				waveColor.r = 53;
			}
			draw_rect(renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, waveColor.raw);
		}
	}
}

//Private

//Unused

WaveEquation::WaveEquation(WaveEquation const &src) {
	*this = src;
}

WaveEquation &WaveEquation::operator=(WaveEquation const &rhs) {
	if (this != &rhs) {
		(void)rhs;
	}
	return *this;
}