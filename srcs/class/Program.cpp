#include "Program.hpp"

Program::Program() : MLXSetup(WIDTH, HEIGHT, false), display(0) {
	std::cout << "Program constructor called" << std::endl;
	try {
		MLXSetup.init();
		renderer = MLXSetup.newImage(WIDTH, HEIGHT);
		map_img = MLXSetup.newImage(WIDTH, HEIGHT);
		wave_img = MLXSetup.newImage(WIDTH, HEIGHT);
	}
	catch (const std::exception &e) {
		exit_error(e.what());
	}

	fill_img(renderer, 0x000000FF);
	fill_img(map_img, 0x000000FF);
	fill_img(wave_img, 0x00000000);
	gameLife.generateGrid();
	map.initMap();
}

Program::~Program() {
	std::cout << "Program destructor called" << std::endl;
}

void Program::run() {
	MLXSetup.imageToWindow(renderer, 0, 0);
	MLXSetup.imageToWindow(wave_img, 0, 0);
	MLXSetup.keyHook(keyhook, this);
	MLXSetup.mouseHook(moosehook, this);
	MLXSetup.loopHook(process, this);
	MLXSetup.loop();
}

//Unused

Program::Program(Program const &src) : MLXSetup(WIDTH, HEIGHT, false), gameLife()  {
	std::cout << "Program copy constructor called" << std::endl;
	*this = src;
}

Program &Program::operator=(Program const &rhs) {
	std::cout << "Program assignment operator called" << std::endl;
	if (this != &rhs) {
		(void)rhs;
	}
	return (*this);
}