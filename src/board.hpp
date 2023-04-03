#ifndef _BOARD_HPP_
#define _BOARD_HPP_
#include "location.hpp"
#include <SFML/Graphics.hpp>

class Board {
public:
	Board() : Board(100){};
	Board(float);
	~Board(){};
	void draw(sf::RenderWindow& window);
	float getSquareSize() { return squareShape[0][0].getSize().x; }
	sf::RectangleShape getSquareShape(Location);
	int getSquare(Location);
	void select(Location);
	void deselect(Location);

private:
	int board[8][8];
	sf::RectangleShape squareShape[8][8];
};

#endif // _BOARD_HPP_