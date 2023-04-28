#include "headers/connection.hpp"
#include "headers/game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

int main(int argc, char** argv) {
	if (argc < 0) throw std::runtime_error("Use at least one argument: -s (starts a server), -c (starts a client)");
	bool isServer = false;
	if (std::string(argv[1]) == "-s") {
		isServer = true;
	} else if (std::string(argv[1]) == "-c") {
		isServer = false;
	} else
		throw std::runtime_error("Argument '" + std::string(argv[1]) + "' not valid!");
	Game game(isServer);
	game.gameLoop();
	return 0;
}
