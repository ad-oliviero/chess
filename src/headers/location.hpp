#ifndef _LOCATION_HPP_
#define _LOCATION_HPP_

#include "common.hpp"
#include <iostream>

class Location {
private:
	unsigned int row;
	unsigned int column;

public:
	Location() : Location(9, 9){};
	Location(unsigned int, unsigned int);
	~Location(){};
	void set(unsigned int, unsigned int);
	unsigned int getRow() const { return row; }
	unsigned int getColumn() const { return column; }
	void check();
	bool operator==(const Location& other) const { return (row == other.row) && (column == other.column); }
	bool operator!=(const Location& other) const { return !(*this == other); }
	friend std::ostream& operator<<(std::ostream&, const Location&);
};

#endif // _LOCATION_HPP_