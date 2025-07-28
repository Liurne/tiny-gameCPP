#include "core/Program.hpp"

int main(int ac, char **av) {
	int	run = 0;

	std::cout << "Welcome in tiny-game CPP working with MLX42" << std::endl;

	if (ac > 1 && std::string(av[1]) == "debug") {
		run = 1;
	}

	Program prgm(run);

	prgm.run();

	return (0);
}