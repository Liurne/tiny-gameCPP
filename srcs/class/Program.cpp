#include "Program.hpp"

Program::Program() : MLXSetup(WIDTH, HEIGHT, false), display(0) {
	std::cout << "Program constructor called" << std::endl;
	nbGeneratedMap = 0;
	try {
		MLXSetup.init();
		renderer = MLXSetup.newImage(WIDTH, HEIGHT);
	}
	catch (const std::exception &e) {
		exit_error(e.what());
	}
	map.initView(MLXSetup);

	mapDisplay = (t_mapDisplay){.displayElement = true, .displayCollectible = true, .displayEnemy = true, .displaySpawn = true};

	fill_img(renderer, 0x000000FF);
	std::cout << "Map generated" << std::endl;
	map.generateMap();
}

Program::~Program() {
	std::cout << "Program destructor called" << std::endl;
}

void Program::run() {
	MLXSetup.imageToWindow(renderer, 0, 0);
	MLXSetup.keyHook(keyhook, this);
	MLXSetup.mouseHook(moosehook, this);
	MLXSetup.loopHook(process, this);
	MLXSetup.loop();
}

//Unused

Program::Program(Program const &src) : MLXSetup(WIDTH, HEIGHT, false) {
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