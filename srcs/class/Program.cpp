#include "Program.hpp"

Program::Program() : MLXSetup(WIDTH, HEIGHT, false), gameLife(), iter(0) {
	std::cout << "Program constructor called" << std::endl;
	try {
		MLXSetup.init();
		renderer = MLXSetup.newImage(WIDTH, HEIGHT);
		cell = MLXSetup.newImage(TILE_SIZE, TILE_SIZE);
	}
	catch (const std::exception &e) {
		exit_error(e.what());
	}

	fill_img(renderer, 0x000000FF);
	fill_img(cell, 0xFFFFFFFF);

	gameLife.generateGrid();
}

Program::~Program() {
	std::cout << "Program destructor called" << std::endl;
}

void Program::run() {
	MLXSetup.imageToWindow(renderer, 0, 0);
	MLXSetup.keyHook(keyhook, this);
	MLXSetup.loopHook(process, this);
	MLXSetup.loop();
}

//Private constructor
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