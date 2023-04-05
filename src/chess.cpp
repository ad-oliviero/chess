#include "headers/chess.hpp"
#include "headers/board.hpp"
#include "headers/piece.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() {
	window.create(sf::VideoMode(800, 800), "chess");
	window.setVerticalSyncEnabled(true);
	setupPieces();
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
					Square& square = board.getSquareHandle(Location(i, j));
					if (square.getShape().getGlobalBounds().contains(cursorPosition)) {
						if (selected) {
							selected->deselect();
							resetPossibilities();
							if (checkMove(getPieceHandle(selected->getLocation()), square)) {
								std::cout << "MOVED from " << getPieceHandle(selected->getLocation()).getLocation() << " to " << square.getLocation() << std::endl;
								movePiece(getPieceHandle(selected->getLocation()), square.getLocation());
							}
							selected = NULL;
						} else {
							selected = square.select();
							allLegalMoves();
							try {
								getPieceHandle(selected->getLocation());
							} catch (const std::runtime_error& e) {
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
		for (auto& p : whites) p.draw(window);
		for (auto& p : blacks) p.draw(window);
		window.display();
	}
}

void Game::setupPieces() {
	setupTeam(whites, Piece::White);
	setupTeam(blacks, Piece::Black);
}

void Game::setupTeam(Piece team[16], bool teamColor) {
	float sqsize				 = board.getSquareHandle(Location(0, 0)).getSize();
	unsigned int voffset = ((teamColor * 8) + !teamColor) - 1;
	for (unsigned int i = 0; i < 8; i++) {
		team[i].setTeam(teamColor);
		team[i].setLocation(i, voffset, sqsize);

		team[8 + i].setTeam(teamColor);
		team[8 + i].setLocation(i, (voffset - (2 * teamColor) + 1), sqsize);
		team[8 + i].setType(PAWN);
		board.getSquareHandle(Location(i, (voffset - (2 * teamColor)) + 1)).setValue(PAWN);
	}

	for (int i = 0; i < 3; i++) {
		place(team[i], TOWER + i);
		place(team[7 - i], TOWER + i);
	}
	place(team[3], QUEEN);
	place(team[4], KING);
}

void Game::place(Piece& piece, unsigned int type) {
	piece.setType(type);
	board.getSquareHandle(piece.getLocation()).setValue(type);
}

void Game::allLegalMoves() {
	if (!selected) return;
	auto& selectedPiece = getPieceHandle(selected->getLocation());
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			auto& sq = board.getSquareHandle(Location(i, j));
			if (checkMove(selectedPiece, sq)) sq.setPossible();
		}
	}
}

void Game::resetPossibilities() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board.getSquareHandle(Location(i, j)).setNotPossible();
		}
	}
}

bool Game::checkMove(Piece& piece, Square square) {
	Location current = piece.getLocation();
	Location target	 = square.getLocation();
	try {
		getPieceHandle(target);
		return false;
	} catch (const std::runtime_error& e) {
	}
	if (current == target) return false;
	Location diff = current - square.getLocation();
	if (piece.getType() == PAWN) {
		if (piece.getTeam() == Piece::White) diff = Location(0, 0) - diff;
		if (diff.getRow() == 0 && diff.getColumn() <= 1) return true;
	} else if (piece.getType() == TOWER) {
		if (diff.getRow() == 0 || diff.getColumn() == 0) return true;
	} else if (piece.getType() == HORSE) {
		if (diff == Location(2, 1) || diff == Location(1, 2)) return true;
	} else if (piece.getType() == BISHOP) {
		if (diff.getRow() == diff.getColumn()) return true;
	} else if (piece.getType() == KING) {
		return true;
	} else if (piece.getType() == QUEEN) {
		return true;
	}
	return false;
}

void Game::movePiece(Piece& piece, Location newLocation) {
	board.getSquareHandle(piece.getLocation()).setValue(NONE);
	Square& newSquare = board.getSquareHandle(newLocation);
	piece.setLocation(newLocation, newSquare.getSize());
	newSquare.setValue(piece.getType());
}

Piece& Game::getPieceHandle(Location location) {
	location.check();
	for (int i = 0; i < 16; i++) {
		if (whites[i].getLocation() == location) return whites[i];
		if (blacks[i].getLocation() == location) return blacks[i];
	}
	throw std::runtime_error("Piece in location: " + location.to_string() + " not found!");
}

int main() {
	Game game;
	game.loop();
	return 0;
}