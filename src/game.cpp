#include "headers/game.hpp"
#include "headers/board.hpp"
#include "headers/piece.hpp"
#include "headers/res_generated.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

Game::Game() : selected(NULL) {
	for (int i = 0; i < 6; i++) {
		textures[i] = new sf::Texture();
		textures[i]->loadFromMemory(images_data[i], images_data_len[i]);
	}
	board = new Board(100, textures);
	window.create(sf::VideoMode(1000, 800), "chess");
	window.setVerticalSyncEnabled(true);
	font.loadFromMemory(font_ttf, font_ttf_len);
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
							if (square.isPossible()) move(*selected, square);
							resetPossibilities();
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
		}
	}
}

void Game::loop() {
	while (window.isOpen()) {
		enventHandler();
		window.clear(sf::Color::Black);
		board->draw(window);
		for (auto& e : eaten) {
			e.x.draw(window);
			window.draw(e.z);
		}
		window.display();
	}
}

void Game::checkStraightMoves(Square& square) {
	Vector2 position = square.getPosition();
	for (int i = position.x + 1; i < 8; i++) {
		Square& target = board->getSquareHandle(i, position.y);
		if (checkMove(square, target)) target.setPossible();
		if (!target.isEmpty()) break;
	}
	for (int i = position.x - 1; i >= 0; i--) {
		Square& target = board->getSquareHandle(i, position.y);
		if (checkMove(square, target)) target.setPossible();
		if (!target.isEmpty()) break;
	}
	for (int i = position.y + 1; i < 8; i++) {
		Square& target = board->getSquareHandle(position.x, i);
		if (checkMove(square, target)) target.setPossible();
		if (!target.isEmpty()) break;
	}
	for (int i = position.y - 1; i >= 0; i--) {
		Square& target = board->getSquareHandle(position.x, i);
		if (checkMove(square, target)) target.setPossible();
		if (!target.isEmpty()) break;
	}
}

void Game::checkDiagonalMoves(Square& square) {
	Vector2 position = square.getPosition();
	for (int i = 1; position.x + i < 8 && position.y + i < 8; i++) {
		Square& target = board->getSquareHandle(position.x + i, position.y + i);
		if (checkMove(square, target)) target.setPossible();
		if (!target.isEmpty()) break;
	}
	for (int i = 1; position.x + i < 8 && position.y - i < 8; i++) {
		Square& target = board->getSquareHandle(position.x + i, position.y - i);
		if (checkMove(square, target)) target.setPossible();
		if (!target.isEmpty()) break;
	}
	for (int i = 1; position.x - i < 8 && position.y + i < 8; i++) {
		Square& target = board->getSquareHandle(position.x - i, position.y + i);
		if (checkMove(square, target)) target.setPossible();
		if (!target.isEmpty()) break;
	}
	for (int i = 1; position.x - i < 8 && position.y - i < 8; i++) {
		Square& target = board->getSquareHandle(position.x - i, position.y - i);
		if (checkMove(square, target)) target.setPossible();
		if (!target.isEmpty()) break;
	}
}

void Game::allLegalMoves(Square& square) {
	unsigned int type = square.getPiece().getType();
	if (type == Piece::TOWER || type == Piece::QUEEN || type == Piece::KING) checkStraightMoves(square);
	if (type == Piece::BISHOP || type == Piece::QUEEN || type == Piece::KING) checkDiagonalMoves(square);
	Vector2 position = square.getPosition();
	if (type == Piece::HORSE) {
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) {
				Square& target = board->getSquareHandle(i, j);
				if (checkMove(square, target)) target.setPossible();
			}
	}
	if (type == Piece::PAWN) {
		for (int i = -1; i <= 1; i += 2) {
			unsigned int yToggle = (-2 * square.getPiece().getTeam()) + 1;
			if (position.x + i < 8 && position.y + yToggle < 8) {
				Square& target = board->getSquareHandle(position.x + i, position.y + yToggle);
				if (!target.isEmpty() && target.getPiece().getTeam() != square.getPiece().getTeam()) target.setPossible();
			}
		}
		if (position.y - 1 < 8) {
			Square& target = board->getSquareHandle(position.x, position.y - 1);
			if (checkMove(square, target)) target.setPossible();
		}
		if (position.y + 1 < 8) {
			Square& target = board->getSquareHandle(position.x, position.y + 1);
			if (checkMove(square, target)) target.setPossible();
		}
	}
}

void Game::resetPossibilities() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board->getSquareHandle(i, j).setNotPossible();
}

bool Game::checkMove(Square& square, Square target) {
	Vector2<unsigned int> diff = square.getPosition() - target.getPosition();
	if (diff == 0) return false;
	Piece& piece = square.getPieceHandle();
	if ((target.getPiece().getType() != Piece::NONE) && (piece.getTeam() == target.getPiece().getTeam())) return false;
	if (piece.getType() == Piece::PAWN) {
		if (piece.getTeam() == Piece::White) diff = Vector2<unsigned int>(0, 0) - diff;
		if (diff.x <= 1 && diff.y <= 1 && target.isEmpty() &&
				(piece.getTeam() == Piece::White
						 ? square.getPosition().y < target.getPosition().y
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
	target.getPieceHandle().setType(square.getPiece().getType(), square.getPiece().getTexture());
	square.empty();
}

void Game::eat(const Square& square) {
	Vector2 position(square.getSize() * (7.0f + ((1.0f * square.getPiece().getTeam()) + 1.0f)), 0.0f);
	sf::Text label("", font, 24);
	for (auto& e : eaten) {
		if (e.x.getTeam() == square.getPiece().getTeam()) {
			if (e.x.getType() == square.getPiece().getType()) {
				e.z.setString("x" + std::to_string(++e.y));
				return;
			}
			if (e.x.getType() != square.getPiece().getType()) position.y += square.getSize();
		}
	}
	label.setPosition(position.x + (square.getSize() * 0.65), position.y + (square.getSize() * 0.75));
	eaten.push_back(Vector3<Piece, unsigned int, sf::Text>(Piece(square.getPiece(), position), 1, label));
}
