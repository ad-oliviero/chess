#include "headers/connection.hpp"
#include "headers/game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

int main(int argc, char** argv) {
	if (argc < 0) throw std::runtime_error("Use at least one argument: -s (starts a server), -c (starts a client)");
	if (std::string(argv[1]) == "-s") {
		try {
			Socket server("127.0.0.1", 5555, Socket::Server);
			std::cout << "Server started!" << std::endl;
			server.run();
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	} else if (std::string(argv[1]) == "-c") {
		Socket cli("127.0.0.1", 5555, Socket::Client);
		std::cout << "Client started!" << std::endl;
		cli.send("Does this work?");
		std::string response = cli.receive();
		std::cout << "Server: " << response << std::endl;
	} else
		throw std::runtime_error("Argument '" + std::string(argv[1]) + "' not valid!");
	// Game game;
	// game.loop();
	return 0;
}