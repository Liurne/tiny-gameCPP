#include "Program.hpp"

int main(int ac, char **av) {
	std::cout << "Welcome in tiny-game CPP working with MLX42" << std::endl;
	if (!ac)
		exit_error(ERR_ARGS);
	std::cout << "You entered: " << av[0] << std::endl;

	Program prgm;

	prgm.run();

	return (0);
}