#include "piece.hpp"
#include "common.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

static const char letters[] = {'P', 'T', 'H', 'B', 'K', 'Q'};

Piece::Piece(uint id, uint type, uint team) {
	if (id > 32) throw std::runtime_error("ID must be < 32!");
	if (type > sizeof(PIECE_TYPE) + 1) throw std::runtime_error("TYPE must be < " + std::to_string(sizeof(PIECE_TYPE) + 1) + "!");
	if (team > 2) throw std::runtime_error("TEAM must be < 2!");

	if (!texture.loadFromFile("res/pawn.png"))
		throw std::runtime_error("Failed to load res/pawn.png");
	sprite.setTexture(texture);
	sprite.setColor(sf::Color::Red);
	sprite.setScale(0.2, 0.2);
	sprite.setPosition(sf::Vector2f(0, 0));

	if (!font.loadFromFile("arial.ttf"))
		throw std::runtime_error("Failed to load arial.ttf");
	label.setFillColor(sf::Color::White);
	label.setOutlineColor(sf::Color::Black);
	label.setFont(font);
	label.setCharacterSize(24);
	label.setOutlineThickness(2.0);
	label.setStyle(sf::Text::Bold);
	label.setString(letters[PAWN]);
}

Piece::~Piece() {
}

void Piece::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(label);
}

void Piece::setLocation(uint row, char column, float squareSize) {
	if (row > 8) throw std::runtime_error("ROW must be < 8!");
	column -= 'a';
	if (column > 'h' - 'a') throw std::runtime_error("COLUMN must be < 'h'!");
	if (column < 0) throw std::runtime_error("COLUMN must be > 'a'!");
	location = {row, column};
	setPosition(row * squareSize, column * squareSize);
}

void Piece::setPosition(float x, float y) {
	sprite.setPosition(x, y);
	sf::Vector2f scale = sprite.getScale();
	sf::Vector2u size	 = texture.getSize();
	sf::Vector2f displacement((size.x * scale.x) / 2, (size.y * scale.y) / 2);
	sf::FloatRect labelSize = label.getLocalBounds();
	displacement.x -= labelSize.width / 2;
	displacement.y -= labelSize.height / 2;
	label.setPosition(x + displacement.x, y + displacement.y);
}

void Piece::setTeam(bool newTeam) {
	team = newTeam;
	sprite.setColor(team == Piece::White ? sf::Color::Green : sf::Color::Red);
}

void Piece::setType(uint newType) {
	if (newType > sizeof(PIECE_TYPE) + 1) throw std::runtime_error("TYPE must be < " + std::to_string(sizeof(PIECE_TYPE) + 1) + "!");
	type = newType;
	label.setString(letters[type]);
}