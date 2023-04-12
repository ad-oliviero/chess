#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "board.hpp"
#include "piece.hpp"
#include "vector3.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
private:
	sf::RenderWindow window;
	sf::Texture* textures[6];
	Board* board;
	Square* selected;
	sf::Font font;
	std::vector<Vector3<Piece, unsigned int, sf::Text>> eaten;

public:
	Game();
	~Game();
	void loop();
	void enventHandler();
	bool checkMove(Square&, Square);
	void checkStraightMoves(Square&);
	void checkDiagonalMoves(Square&);
	void allLegalMoves(Square&);
	void resetPossibilities();
	void move(Square&, Square&);
	void eat(const Square&);
};

#endif