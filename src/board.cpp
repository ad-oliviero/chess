#include "board.hpp"
#include "common.hpp"
#include <SFML/Graphics.hpp>

Board::Board(float squaresz) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = 0;
			squareShape[i][j].setSize(sf::Vector2f(squaresz, squaresz));
			squareShape[i][j].setPosition(sf::Vector2f(i * squaresz, j * squaresz));
			squareShape[i][j].setFillColor(((i + j) % 2 == 0) ? sf::Color(200, 200, 200, 255) : sf::Color(50, 50, 50, 255));
		}
	}
}

void Board::draw(sf::RenderWindow& window) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			window.draw(squareShape[i][j]);
		}
	}
}

sf::RectangleShape Board::getSquareShape(Location location) {
	location.check();
	return squareShape[location.getRow()][location.getColumn()];
}

int Board::getSquare(Location location) {
	location.check();
	return board[location.getRow()][location.getColumn()];
}