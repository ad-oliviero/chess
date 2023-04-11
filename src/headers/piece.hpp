#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#include "vector2.hpp"
#include <SFML/Graphics.hpp>

class Piece {
private:
	sf::Sprite sprite;
	sf::Texture* texture;
	unsigned int type;
	bool team;

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
	unsigned int getType() const { return type; }
	bool getTeam() const { return team; }
	sf::Texture* getTexture() const { return texture; }

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
};

#endif // _PIECE_HPP_