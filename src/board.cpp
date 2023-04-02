#include "board.hpp"
#include <SFML/Graphics.hpp>

Board::Board(float squaresz) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = 0;
			square[i][j].setSize(sf::Vector2f(squaresz, squaresz));
			square[i][j].setPosition(sf::Vector2f(i * squaresz, j * squaresz));
			square[i][j].setFillColor(((i + j) % 2 == 0) ? sf::Color::White : sf::Color::Black);
		}
	}
}

Board::~Board() {
}

void Board::draw(sf::RenderWindow& window) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			window.draw(square[i][j]);
		}
	}
}