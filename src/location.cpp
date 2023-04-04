#include "headers/location.hpp"
#include <iostream>

Location::Location(uint row, char column) {
	set(row, column);
}

void Location::check() {
	if (row > 8) throw std::runtime_error("row value must be less than 8!");
	if (column > 8) throw std::runtime_error("column value must be less than 8!");
}

void Location::set(uint row, char column) {
	this->row		 = row;
	this->column = column;
}