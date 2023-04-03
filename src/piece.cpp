#include "piece.hpp"
#include "common.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

static const std::string piece_name[] = {"pawn", "tower", "horse", "bishop", "king", "queen"};

Piece::Piece(uint type, uint team) {
	this->setType(type);
	this->setTeam(team);

	sprite.setTexture(texture);
	sprite.setColor(sf::Color::White);
	sprite.setScale(0.2, 0.2);
	sprite.setPosition(sf::Vector2f(0, 0));
}

void Piece::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Piece::setLocation(uint row, char column, float squareSize) {
	if (row > 8) throw std::runtime_error("ROW must be < 8!");
	column -= 'a';
	if (column > 'h' - 'a') throw std::runtime_error("COLUMN must be < 'h'!");
	if (column < 0) throw std::runtime_error("COLUMN must be > 'a'!");
	location.set(row, column);
	setPosition(row * squareSize, column * squareSize);
}

void Piece::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

void Piece::setTeam(bool newTeam) {
	if (team > 2) throw std::runtime_error("TEAM must be < 2!");
	team = newTeam;
	sprite.setColor(team == Piece::White ? sf::Color::White : sf::Color(95, 95, 95, 255));
}

void Piece::setType(uint newType) {
	if (newType > sizeof(PIECE_TYPE) + 1) throw std::runtime_error("TYPE must be < " + std::to_string(sizeof(PIECE_TYPE) + 1) + "!");
	type = newType;
	if (!texture.loadFromFile("../res/" + piece_name[this->type] + ".png"))
		throw std::runtime_error("Failed to load ../res/" + piece_name[this->type] + ".png");
}