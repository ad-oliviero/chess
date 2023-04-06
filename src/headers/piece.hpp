#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#include "common.hpp"
#include <SFML/Graphics.hpp>

class Piece {
public:
	Piece() : Piece(NONE, White){};
	Piece(unsigned int, bool);
	~Piece(){};
	void draw(sf::RenderWindow&) const;
	void setPosition(float, float);
	void setPosition(float, float, float);
	void setTeam(bool);
	void setType(unsigned int);
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
	unsigned int type;
	bool team;
};

#endif // _PIECE_HPP_