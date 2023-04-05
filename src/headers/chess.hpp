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
	void enventHandler();
	void place(Piece&, unsigned int);
	bool checkMove(Piece&, Square);
	void allLegalMoves();
	void resetPossibilities();
	void movePiece(Piece&, Location);
	Piece& getPieceHandle(Location);

private:
	sf::RenderWindow window;
	Board board;
	Square* selected;
	Piece blacks[16];
	Piece whites[16];
};

#endif