#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

#include "location.hpp"
#include <SFML/Graphics.hpp>

class Square {
public:
	Square() : Square(100, 0, 0, sf::Color(200, 200, 200, 255)) {}
	Square(float, float, float, sf::Color);
	~Square(){};
	void setColor(sf::Color);
	void setSize(float);
	void setPosition(Location);
	void draw(sf::RenderWindow&);
	float getSize() { return shape.getSize().x; }
	sf::RectangleShape& getShape() { return shape; }
	int getValue() { return value; }
	Square* select();
	void deselect();

private:
	sf::RectangleShape shape;
	sf::RectangleShape selectShape;
	Location location;
	int value;
};

#endif // _SQUARE_HPP_