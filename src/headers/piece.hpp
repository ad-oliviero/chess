#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#include "common.hpp"
#include "location.hpp"
#include <SFML/Graphics.hpp>

class Piece {
public:
	Piece() : Piece(0, 0){};
	Piece(unsigned int, unsigned int);
	~Piece(){};
	void draw(sf::RenderWindow&);
	void setLocation(unsigned int, unsigned int);
	void setLocation(Location);
	void setLocation(unsigned int, unsigned int, float);
	void setLocation(Location, float);
	void setPosition(float, float);
	void setTeam(bool);
	void setType(unsigned int);
	Location getLocation() { return location; }
	unsigned int getType() { return type; }
	bool getTeam() { return team; }

	enum Team {
		White,
		Black
	};

private:
	sf::Texture texture;
	sf::Font font;
	sf::Sprite sprite;
	Location location;
	unsigned int type;
	bool team;
};

#endif // _PIECE_HPP_