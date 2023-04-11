#include "headers/vector2.hpp"
#include <sstream>

template <typename xType, typename yType>
std::string Vector2<xType, yType>::to_string() {
	std::ostringstream oss;
	oss << *this;
	return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Vector2<unsigned int>& v) {
	os << "[" << v.x << ", " << v.y << "]";
	return os;
}