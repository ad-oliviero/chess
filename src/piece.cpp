#include "headers/piece.hpp"
#include "headers/common.hpp"
#include "headers/images.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

Piece::Piece(unsigned int type, unsigned int team) {
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

void Piece::setLocation(unsigned int row, unsigned int column, float squareSize) {
	setLocation(row, column);
	setPosition(row * squareSize, column * squareSize);
}

void Piece::setLocation(Location location) {
	setLocation(location.getRow(), location.getColumn());
}

void Piece::setLocation(Location location, float squareSize) {
	setLocation(location.getRow(), location.getColumn());
	setPosition(location.getRow() * squareSize, location.getColumn() * squareSize);
}

void Piece::setLocation(unsigned int row, unsigned int column) {
	location.set(row, column);
	location.check();
}

void Piece::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

void Piece::setTeam(bool newTeam) {
	team = newTeam;
	sprite.setColor(team == Piece::White ? sf::Color::White : sf::Color(95, 95, 95, 255));
}

void Piece::setType(unsigned int newType) {
	if (newType > QUEEN + 1) throw std::runtime_error("TYPE must be < " + std::to_string(QUEEN + 1) + "!");
	type = newType;
	texture.loadFromMemory(images_data[type], images_data_len[type]);
}
