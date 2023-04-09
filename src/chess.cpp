#include "headers/chess.hpp"
#include "headers/board.hpp"
#include "headers/images.hpp"
#include "headers/piece.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() {
	for (int i = 0; i < 6; i++) {
		textures[i] = new sf::Texture();
		textures[i]->loadFromMemory(images_data[i], images_data_len[i]);
	}
	board = new Board(100, textures);
	window.create(sf::VideoMode(1000, 800), "chess");
	window.setVerticalSyncEnabled(true);
	selected = NULL;
}

Game::~Game() {
	window.close();
	for (auto& t : textures)
		delete t;
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
					Square& square = board->getSquareHandle(i, j);
					if (square.getShape().getGlobalBounds().contains(cursorPosition)) {
						if (selected) {
							selected->deselect();
							resetPossibilities();
							if (checkMove(*selected, square)) {
								move(*selected, square);
								std::cout << "MOVED from " << selected->getPosition() << " to " << square.getPosition() << std::endl;
							}
							selected = NULL;
						} else {
							selected = square.select();
							allLegalMoves(*selected);
							if (selected->getPiece().getType() == Piece::NONE) {
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
	// Piece piec;
	// sf::Texture* txt = new sf::Texture;
	// txt->loadFromMemory(images_data[0], images_data_len[0]);
	// piec.sprite.setTexture(*txt);
	while (window.isOpen()) {
		enventHandler();
		window.clear(sf::Color::Black);
		board->draw(window);
		for (auto& e : eaten) e.draw(window);
		window.display();
	}
}

void Game::allLegalMoves(Square& square) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			Square& target = board->getSquareHandle(i, j);
			if (checkMove(square, target)) target.setPossible();
		}
}

void Game::resetPossibilities() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board->getSquareHandle(i, j).setNotPossible();
		}
	}
}

bool Game::checkMove(Square& square, Square target) {
	if (square.getPiece().getTeam() == Piece::NONE) return false;
	Vector2<unsigned int> diff = square.getPosition() - target.getPosition();
	if (diff == 0) return false;
	Piece& piece = square.getPieceHandle();
	if ((target.getPiece().getType() != Piece::NONE) && (piece.getTeam() == target.getPiece().getTeam())) return false;
	if (piece.getType() == Piece::PAWN) {
		if (piece.getTeam() == Piece::White) diff = Vector2<unsigned int>(0, 0) - diff;
		if (diff.x == 0 && diff.y <= 1 &&
				(piece.getTeam() == Piece::White ? square.getPosition().y < target.getPosition().y
																				 : square.getPosition().y > target.getPosition().y)) return true;
	} else if (piece.getType() == Piece::TOWER) {
		if (diff.x == 0 || diff.y == 0) return true;
	} else if (piece.getType() == Piece::HORSE) {
		if (diff == Vector2<unsigned int>(2, 1) || diff == Vector2<unsigned int>(1, 2)) return true;
	} else if (piece.getType() == Piece::BISHOP) {
		if (diff.x == diff.y) return true;
	} else if (piece.getType() == Piece::KING) {
		if (diff.x <= 1 && diff.y <= 1) return true;
	} else if (piece.getType() == Piece::QUEEN) {
		if ((diff.x == 0 || diff.y == 0) || (diff.x == diff.y)) return true;
	}
	return false;
}

void Game::move(Square& square, Square& target) {
	if (target.getPiece().getType() != Piece::NONE) eat(target);
	target.getPieceHandle().setTeam(square.getPiece().getTeam());
	target.getPieceHandle().setType(square.getPiece().getType());
	square.empty();
}

void Game::eat(const Square& square) {
	eaten.push_back(Piece(square.getPiece(), Vector2(square.getSize() * 8.0f, 0.0f)));
}

int main() {
	Game game;
	game.loop();
	return 0;
}