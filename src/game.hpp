#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "board.hpp"
#include "piece.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	~Game();
	void loop();
	void setupPieces();
	void setupTeam(Piece[16], bool);

private:
	sf::RenderWindow window;
	Board board;
	Piece blacks[16];
	Piece whites[16];
};

#endif