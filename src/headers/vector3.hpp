#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include "vector2.hpp"
#include <string>

template <typename xType, typename yType = xType, typename zType = yType>
class Vector3 {
public:
	xType x;
	yType y;
	zType z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(xType x, yType y, zType z) : x(x), y(y), z(z) {}
	~Vector3() {}
	std::string to_string();
	bool operator==(const Vector3& other) const { return (x == other.x) && (y == other.y) && (z = other.z); }
	bool operator==(const xType& other) const { return (x == other) && (y == other) && (z == other); }
	bool operator!=(const Vector3& other) const { return !(*this == other); }
	Vector3 operator+(const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
	Vector3 operator-(const Vector3& other) const { return Vector3(std::abs(int(x - other.x)), std::abs(int(y - other.y)), std::abs(int(z - other.z))); }
	friend std::ostream& operator<<(std::ostream&, const Vector3<unsigned int>&);
};

#endif // _VECTOR3_HPP_