#include "headers/board.hpp"
#include "headers/vector2.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Board::Board(float squaresz, sf::Texture* textures[6]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			squares[i][j].setSize(squaresz);
			squares[i][j].setColor(((i + j) % 2 == 0) ? sf::Color(200, 200, 200, 255) : sf::Color(50, 50, 50, 255));
			squares[i][j].setPosition(i, j);
		}
	}

	setupTeam(Piece::White, textures);
	setupTeam(Piece::Black, textures);
}

void Board::setupTeam(bool color, sf::Texture* textures[6]) {
	float sqsize = squares[0][0].getSize();
	for (unsigned int i = 0; i < 8; i++) {
		auto& piece					 = squares[i][7 * color].getPieceHandle();
		auto& pieceSecondRow = squares[i][1 + (5 * color)].getPieceHandle();
		piece.setTeam(color);

		pieceSecondRow.setTeam(color);
		pieceSecondRow.setType(Piece::PAWN, textures[Piece::PAWN]);
	}

	for (int i = 0; i < 8; i += 7) {
		/* why am I accessing the square by [j][i] and not [i][j] as per convention?
		 * maybe I'm stupid as it took me about 2h to understand why "the pieces were placed vertically"
		 * the way I understand this is that we should not think at the squares array as a bi-dimentional array (matrix)
		 * but rather as a table accessed by coordinates, so the first one is the x (and it goes from 0 to 8)
		 * and the y (we access only 0, 1, 6 and 7).
		 */
		for (int j = 0; j < 3; j++) {
			auto type = Piece::TOWER + j;
			squares[j][i].getPieceHandle().setType(type, textures[type]);
			squares[7 - j][i].getPieceHandle().setType(type, textures[type]);
		}
		squares[3][i].getPieceHandle().setType(Piece::QUEEN, textures[Piece::QUEEN]);
		squares[4][i].getPieceHandle().setType(Piece::KING, textures[Piece::KING]);
	}
}

void Board::draw(sf::RenderWindow& window) const {
	for (auto& r : squares)
		for (auto& s : r) s.draw(window);
}

std::ostream& operator<<(std::ostream& os, const Board& b) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			os << b.getSquare(j, i).getPiece().getType() << "  ";
		os << '\n';
	}
	return os;
}