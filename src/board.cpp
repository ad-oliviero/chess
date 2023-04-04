#include "headers/board.hpp"
#include "headers/common.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Board::Board(float squaresz) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			squares[i][j].setSize(squaresz);
			squares[i][j].setColor(((i + j) % 2 == 0) ? sf::Color(200, 200, 200, 255) : sf::Color(50, 50, 50, 255));
			squares[i][j].setPosition(Location(i, j));
		}
	}
}

void Board::draw(sf::RenderWindow& window) const {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			squares[i][j].draw(window);
}

const Square& Board::getSquare(Location location) const {
	location.check();
	return squares[location.getRow()][location.getColumn()];
}

Square& Board::getSquareHandle(Location location) {
	location.check();
	return squares[location.getRow()][location.getColumn()];
}

std::ostream& operator<<(std::ostream& os, const Board& b) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			os << b.getSquare(Location(j, i)).getValue() << "  ";
		}
		os << '\n';
	}
	return os;
}