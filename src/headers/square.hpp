#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

#include "piece.hpp"
#include "vector2.hpp"
#include <SFML/Graphics.hpp>

class Square {
public:
	Square() : Square(100, 0, 0, sf::Color(200, 200, 200, 255)) {}
	Square(float, float, float, sf::Color);
	~Square(){};
	void setColor(sf::Color);
	void setSize(float);
	void setPosition(unsigned int, unsigned int);
	void setPiece(Piece);
	void setPossible();
	void setNotPossible();
	void empty();
	void draw(sf::RenderWindow&) const;
	float getSize() { return shape.getSize().x; }
	sf::RectangleShape& getShape() { return shape; }
	const Vector2u& getPosition() const { return position; }
	Piece getPiece() const { return piece; }
	Piece& getPieceHandle() { return piece; }
	Square* select();
	void deselect();

private:
	sf::RectangleShape shape;
	sf::RectangleShape selectShape;
	sf::CircleShape possibleShape;
	Vector2u position;
	Piece piece;
};

#endif // _SQUARE_HPP_