#ifndef WAVEEQUATION_HPP
# define WAVEEQUATION_HPP

#include "game_rule.h"
#include "MLXWrapper.hpp"

const float c = 0.4f;
const float dt = 0.1f;
const float damping = 0.998f;

class WaveEquation {
public:
	WaveEquation();
	~WaveEquation();

	void init();
	void upadate();
	void drop(int x, int y, float amplitude);
	void display(mlx_image_t *renderer);

private:
	std::vector<std::vector<float> > grid;
	std::vector<std::vector<float> > old_grid;

	int width;
	int height;

	WaveEquation(WaveEquation const &src);
	WaveEquation &operator=(WaveEquation const &rhs);

};

#endif