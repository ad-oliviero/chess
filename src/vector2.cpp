#include "headers/vector2.hpp"
#include <sstream>

std::string Vector2u::to_string() {
	std::ostringstream oss;
	oss << *this;
	return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Vector2u& v) {
	os << "[" << v.x << ", " << v.x << "]";
	return os;
}