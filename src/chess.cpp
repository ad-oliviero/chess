#include "headers/chess.hpp"
#include "headers/board.hpp"
#include "headers/piece.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() {
	window.create(sf::VideoMode(800, 800), "chess");
	window.setVerticalSyncEnabled(true);
	selected = NULL;
}

Game::~Game() {
	window.close();
}

void Game::enventHandler() {
	sf::Vector2f cursorPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			for (unsigned int i = 0; i < 8; i++) {
				for (unsigned int j = 0; j < 8; j++) {
					Square& square = board.getSquareHandle(i, j);
					if (square.getShape().getGlobalBounds().contains(cursorPosition)) {
						if (selected) {
							selected->deselect();
							resetPossibilities();
							if (checkMove(*selected, square)) {
								std::cout << "MOVED from " << selected->getPosition() << " to " << square.getPosition() << std::endl;
								move(*selected, square);
							}
							selected = NULL;
						} else {
							selected = square.select();
							allLegalMoves(*selected);
							if (selected->getPiece().getType() == NONE) {
								selected->deselect();
								resetPossibilities();
								selected = NULL;
							}
						}
					}
				}
			}
			// std::cout << board << std::endl;
		}
		// else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	}
}

void Game::loop() {
	while (window.isOpen()) {
		enventHandler();
		window.clear(sf::Color::Black);
		board.draw(window);
		window.display();
	}
}

void Game::allLegalMoves(Square& square) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			Square& target = board.getSquareHandle(i, j);
			if (checkMove(square, target)) target.setPossible();
		}
}

void Game::resetPossibilities() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board.getSquareHandle(i, j).setNotPossible();
		}
	}
}

bool Game::checkMove(Square& square, Square target) {
	if (square.getPiece().getTeam() == NONE) return false;
	Vector2u diff = square.getPosition() - target.getPosition();
	if (diff == 0) return false;
	Piece& piece = square.getPieceHandle();
	if ((target.getPiece().getType() != NONE) && (piece.getTeam() == target.getPiece().getTeam())) return false;
	if (piece.getType() == PAWN) {
		if (piece.getTeam() == Piece::White) diff = Vector2u(0, 0) - diff;
		if (diff.x == 0 && diff.y <= 1 &&
				(piece.getTeam() == Piece::White ? square.getPosition().y < target.getPosition().y
																				 : square.getPosition().y > target.getPosition().y)) return true;
	} else if (piece.getType() == TOWER) {
		if (diff.x == 0 || diff.y == 0) return true;
	} else if (piece.getType() == HORSE) {
		if (diff == Vector2u(2, 1) || diff == Vector2u(1, 2)) return true;
	} else if (piece.getType() == BISHOP) {
		if (diff.x == diff.y) return true;
	} else if (piece.getType() == KING) {
		if (diff.x <= 1 && diff.y <= 1) return true;
	} else if (piece.getType() == QUEEN) {
		if ((diff.x == 0 || diff.y == 0) || (diff.x == diff.y)) return true;
	}
	return false;
}

void Game::move(Square& square, Square& target) {
	target.setPiece(square.getPiece());
	square.empty();
}

int main() {
	Game game;
	game.loop();
	return 0;
}