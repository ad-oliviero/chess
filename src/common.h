#ifndef _COMMON_H_
#define _COMMON_H_

enum PIECE_TYPE {
	PAWN,
	TOWER,
	HORSE,
	BISHOP,
	KING,
	QUEEN
};

typedef struct location_t {
	unsigned int row;
	char column;
} Location;

#endif // _COMMON_H_