#include "headers/piece.hpp"
#include "headers/vector2.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

Piece::Piece(unsigned int type, bool team) {
	texture = NULL;
	setTeam(team);
	setType(type);
	sprite.setScale(0.2, 0.2);
	sprite.setPosition(sf::Vector2f(0, 0));
}

Piece::Piece(const Piece& piece, Vector2<float> eatenSpace) {
	setTeam(piece.team);
	setType(piece.type, piece.getTexture());
	sprite.setScale(0.2, 0.2);
	setPosition(eatenSpace);
}

void Piece::draw(sf::RenderWindow& window) const {
	window.draw(sprite);
}

void Piece::setPosition(float x, float y, float squaresz) {
	setPosition(x * squaresz, y * squaresz);
}

void Piece::setPosition(Vector2<float> position) {
	setPosition(position.x, position.y);
}

void Piece::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

void Piece::setTeam(bool team) {
	this->team = team;
	sprite.setColor(this->team == Piece::White ? sf::Color::White : sf::Color(95, 95, 95, 255));
}

void Piece::setType(unsigned int type, sf::Texture* texture) {
	this->texture = texture;
	setType(type);
}

void Piece::setType(unsigned int type) {
	this->type = type;
	if (this->type == NONE) {
		sprite.setColor(sf::Color(0, 0, 0, 0));
		return;
	}
	if (texture) sprite.setTexture(*texture);
}

Piece& Piece::operator=(const Piece& other) {
	if (this != &other) {
		sprite = other.sprite;
		team	 = other.team;
		setType(other.type);
	}
	return *this;
}
