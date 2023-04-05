#include "headers/location.hpp"
#include <iostream>
#include <sstream>

Location::Location(unsigned int row, unsigned int column) {
	set(row, column);
}

void Location::check() {
	if (row > 8) throw std::runtime_error("row value must be less than 8!");
	if (column > 8) throw std::runtime_error("column value must be less than 8!");
}

std::string Location::to_string() {
	std::ostringstream oss;
	oss << *this;
	return oss.str();
}

void Location::set(unsigned int row, unsigned int column) {
	this->row		 = row;
	this->column = column;
}

std::ostream& operator<<(std::ostream& os, const Location& l) {
	os << "[" << l.getRow() << ", " << l.getColumn() << "]";
	return os;
}