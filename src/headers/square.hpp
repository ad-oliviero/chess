#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

#include "piece.hpp"
#include "vector2.hpp"
#include <SFML/Graphics.hpp>

class Square {
private:
	sf::RectangleShape shape;
	sf::RectangleShape selectShape;
	sf::CircleShape possibleShape;
	Vector2<unsigned int> position;
	Piece piece;
	bool possible;

public:
	Square() : Square(100, 0, 0, sf::Color(200, 200, 200, 255)) {}
	Square(float, float, float, sf::Color);
	~Square(){};
	void setColor(sf::Color);
	void setSize(float);
	void setPosition(unsigned int, unsigned int);
	void setPossible();
	void setNotPossible();
	void empty();
	Square* select();
	void deselect();
	void draw(sf::RenderWindow&) const;
	bool isEmpty() const { return piece.getType() == Piece::NONE; }
	bool isPossible() const { return possible; }
	float getSize() const { return shape.getSize().x; }
	sf::RectangleShape& getShape() { return shape; }
	const Vector2<unsigned int>& getPosition() const { return position; }
	const Piece& getPiece() const { return piece; }
	Piece& getPieceHandle() { return piece; }
	bool operator==(const Square& other) const { return position == other.position; }
	bool operator!=(const Square& other) const { return !(*this == other); }
};

#endif // _SQUARE_HPP_