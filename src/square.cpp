#include "headers/square.hpp"

Square::Square(float size, float x, float y, sf::Color color) {
	shape.setSize(sf::Vector2f(size, size));
	shape.setFillColor(color);

	selectShape.setSize(sf::Vector2f(size, size));
	selectShape.setFillColor(sf::Color(0, 0, 0, 0));

	possibleShape.setRadius(size / 3);
	setNotPossible();
}

void Square::setColor(sf::Color color) {
	shape.setFillColor(color);
}

void Square::setSize(float size) {
	shape.setSize(sf::Vector2f(size, size));
}

void Square::setPosition(unsigned int x, unsigned int y) {
	position	 = Vector2<unsigned int>(x, y);
	float size = shape.getSize().x;
	float nx	 = x * size;
	float ny	 = y * size;
	shape.setPosition(sf::Vector2f(nx, ny));
	selectShape.setPosition(sf::Vector2f(nx, ny));
	possibleShape.setPosition(sf::Vector2f(nx + (size / 5), ny + (size / 5)));
	piece.setPosition(x, y, size);
}

void Square::setPossible() {
	possibleShape.setFillColor(sf::Color(100, 150, 100, 75));
}

void Square::setNotPossible() {
	possibleShape.setFillColor(sf::Color(0, 0, 0, 0));
}

void Square::empty() {
	piece.setType(Piece::NONE);
}

void Square::draw(sf::RenderWindow& window) const {
	window.draw(shape);
	window.draw(possibleShape);
	window.draw(selectShape);
	piece.draw(window);
}

Square* Square::select() {
	selectShape.setFillColor(sf::Color(0, 255, 0, 155));
	return this;
}

void Square::deselect() {
	selectShape.setFillColor(sf::Color(0, 255, 0, 0));
}