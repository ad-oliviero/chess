#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#include "common.hpp"
#include "location.hpp"
#include <SFML/Graphics.hpp>

class Piece {
public:
	Piece() : Piece(0, 0){};
	Piece(uint, uint);
	~Piece(){};
	void draw(sf::RenderWindow&);
	void setLocation(uint, char, float);
	void setPosition(float, float);
	void setTeam(bool);
	void setType(uint);

	enum Team {
		White,
		Black
	};

private:
	sf::Texture texture;
	sf::Font font;
	sf::Sprite sprite;
	Location location;
	uint type;
	bool team;
};

#endif // _PIECE_HPP_