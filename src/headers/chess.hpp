#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "board.hpp"
#include "piece.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
public:
	Game();
	~Game();
	void loop();
	void enventHandler();
	bool checkMove(Square&, Square);
	void allLegalMoves(Square&);
	void resetPossibilities();
	void move(Square&, Square&);
	void eat(const Square&);

private:
	sf::RenderWindow window;
	sf::Texture* textures[6];
	Board* board;
	Square* selected;
	std::vector<Piece> eaten;
};

#endif