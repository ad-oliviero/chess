#include "headers/vector3.hpp"
#include <sstream>

template <typename xType, typename yType, typename zType>
std::string Vector3<xType, yType, zType>::to_string() {
	std::ostringstream oss;
	oss << *this;
	return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Vector3<unsigned int>& v) {
	os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}