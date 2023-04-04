#include "headers/square.hpp"
#include "headers/common.hpp"

Square::Square(float size, float x, float y, sf::Color color) {
	value = NONE;
	location.set(0, 0);
	shape.setSize(sf::Vector2f(size, size));
	shape.setFillColor(color);

	selectShape.setSize(sf::Vector2f(size, size));
	selectShape.setFillColor(sf::Color(0, 0, 0, 0));
}

void Square::setColor(sf::Color color) {
	shape.setFillColor(color);
}

void Square::setSize(float size) {
	shape.setSize(sf::Vector2f(size, size));
}

void Square::setPosition(Location location) {
	location.check();
	this->location = location;
	float x				 = this->location.getRow() * shape.getSize().x;
	float y				 = this->location.getColumn() * shape.getSize().y;
	shape.setPosition(sf::Vector2f(x, y));
	selectShape.setPosition(sf::Vector2f(x, y));
}

void Square::setValue(unsigned int value) {
	this->value = value;
}

void Square::draw(sf::RenderWindow& window) const {
	window.draw(shape);
	window.draw(selectShape);
}

Square* Square::select() {
	selectShape.setFillColor(sf::Color(0, 255, 0, 155));
	return this;
}

void Square::deselect() {
	selectShape.setFillColor(sf::Color(0, 255, 0, 0));
}