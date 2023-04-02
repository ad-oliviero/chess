#ifndef _BOARD_HPP_
#define _BOARD_HPP_
#include <SFML/Graphics.hpp>

class Board {
public:
	Board() : Board(100){};
	Board(float);
	~Board();
	void draw(sf::RenderWindow& window);
	float getSquareSize() { return square[0][0].getSize().x; }

private:
	int board[8][8];
	sf::RectangleShape square[8][8];
};

#endif // _BOARD_HPP_