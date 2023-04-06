#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#include "common.hpp"
#include "vector2.hpp"
#include <SFML/Graphics.hpp>

class Piece {
public:
	Piece() : Piece(NONE, White) {}
	Piece(unsigned int type, bool team);
	Piece(const Piece&, Vector2<float>);
	~Piece(){};
	void draw(sf::RenderWindow&) const;
	void setPosition(float, float);
	void setPosition(float, float, float);
	void setPosition(Vector2<float>);
	void setTeam(bool);
	void setType(unsigned int);
	void setEaten(Vector2<float>);
	Piece& operator=(const Piece&);
	unsigned int getType() { return type; }
	bool getTeam() { return team; }

	enum Team {
		White,
		Black
	};

private:
	sf::Texture texture;
	sf::Sprite sprite;
	unsigned int type;
	bool team;
};

#endif // _PIECE_HPP_