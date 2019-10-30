#include <iostream>
#include "gManager.hpp"

int main(int argc, char **argv)
{
	bool is_dynamic_switching_enabled = true;
	int libNum = 1;

	if (argc > 2){
		std::cout << "Too much arguments" << std::endl;
		return (0);
	}
	else if (argc == 2)
	{
		if (strlen(argv[1]) > 1)
		{
			std::cout << "Wrong library number" << std::endl;
			return (0);
		}
		try {
			libNum = std::stoi(argv[1]);
			is_dynamic_switching_enabled = false;
		}
		catch (std::exception &e) {
			std::cout << "Error " << e.what() << std::endl;
			return (0);
		}
	}
	if (libNum >= 1 && libNum <= 3)
	{
		std::unique_ptr<gManager> game = std::make_unique<gManager>(is_dynamic_switching_enabled);
		if (game->Init(640, 480, libNum))
			game->run();
	}
	else {
		std::cout << "Wrong library number" << std::endl;
		return (0);
	}
	return (0);
}