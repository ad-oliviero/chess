#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

#include "location.hpp"
#include "piece.hpp"
#include <SFML/Graphics.hpp>

class Square {
public:
	Square() : Square(100, 0, 0, sf::Color(200, 200, 200, 255)) {}
	Square(float, float, float, sf::Color);
	~Square(){};
	void setColor(sf::Color);
	void setSize(float);
	void setPosition(Location);
	void setValue(unsigned int);
	void draw(sf::RenderWindow&) const;
	float getSize() { return shape.getSize().x; }
	sf::RectangleShape& getShape() { return shape; }
	int getValue() const { return value; }
	Location getLocation() const { return location; }
	void setPossible();
	void setNotPossible();
	Square* select();
	void deselect();

private:
	sf::RectangleShape shape;
	sf::RectangleShape selectShape;
	sf::CircleShape possibleShape;
	Location location;
	unsigned int value;
};

#endif // _SQUARE_HPP_