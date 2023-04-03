#ifndef _LOCATION_HPP_
#define _LOCATION_HPP_

#include "common.hpp"

class Location {
private:
	uint row;
	char column;

public:
	Location() : Location(9, 9){};
	Location(uint, char);
	~Location(){};
	void set(uint, char);
	uint getRow() { return row; }
	char getColumn() { return column; }
	void check();
	bool operator==(const Location& other) const { return (row == other.row) && (column == other.column); }
	bool operator!=(const Location& other) const { return !(*this == other); }
};

#endif // _LOCATION_HPP_