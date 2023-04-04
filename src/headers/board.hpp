#ifndef _BOARD_HPP_
#define _BOARD_HPP_
#include "location.hpp"
#include "square.hpp"
#include <SFML/Graphics.hpp>

class Board {
public:
	Board() : Board(100) {}
	Board(float);
	~Board(){};
	void draw(sf::RenderWindow&) const;
	const Square& getSquare(Location) const;
	Square& getSquareHandle(Location);
	friend std::ostream& operator<<(std::ostream& os, const Board& b);

private:
	Square squares[8][8];
};

#endif // _BOARD_HPP_