#include "headers/piece.hpp"
#include "headers/common.hpp"
#include "headers/images.hpp"
#include "headers/vector2.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

Piece::Piece(unsigned int type, bool team) {
	setTeam(team);
	setType(type);
	sprite.setScale(0.2, 0.2);
	sprite.setPosition(sf::Vector2f(0, 0));
}

Piece::Piece(const Piece& piece, Vector2<float> eatenSpace) {
	setType(piece.type);
	setTeam(piece.team);
	sprite.setScale(0.2, 0.2);
	texture.loadFromMemory(images_data[this->type], images_data_len[this->type]);
	sprite.setTexture(texture);
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

void Piece::setType(unsigned int type) {
	this->type = type;
	if (this->type == NONE) {
		sprite.setColor(sf::Color(0, 0, 0, 0));
		return;
	}
	texture.loadFromMemory(images_data[this->type], images_data_len[this->type]);
	sprite.setTexture(texture);
}

Piece& Piece::operator=(const Piece& other) {
	if (this != &other) {
		sprite = other.sprite;
		team	 = other.team;
		setType(other.type);
	}
	return *this;
}
