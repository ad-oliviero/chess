#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#include "vector2.hpp"
#include <SFML/Graphics.hpp>

class Piece {
public:
	void setTexture(sf::Texture* txt) { sprite.setTexture(*txt); }
	Piece() : Piece(NONE, White) {}
	Piece(unsigned int type, bool team);
	Piece(const Piece&, Vector2<float>);
	~Piece(){};
	void draw(sf::RenderWindow&) const;
	void setPosition(float, float);
	void setPosition(float, float, float);
	void setPosition(Vector2<float>);
	void setTeam(bool);
	void setType(unsigned int, sf::Texture*);
	void setType(unsigned int);
	void setEaten(Vector2<float>);
	Piece& operator=(const Piece&);
	unsigned int getType() { return type; }
	bool getTeam() { return team; }

	enum TEAM {
		White,
		Black
	};

	enum TYPE {
		PAWN,
		TOWER,
		HORSE,
		BISHOP,
		KING,
		QUEEN,
		NONE = 9
	};

private:
	sf::Sprite sprite;
	sf::Texture* texture;
	unsigned int type;
	bool team;
};

#endif // _PIECE_HPP_