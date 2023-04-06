#ifndef _VECTOR2_HPP_
#define _VECTOR2_HPP_

#include <string>

class Vector2u {
public:
	unsigned int x;
	unsigned int y;

	Vector2u() : Vector2u(0, 0) {}
	Vector2u(unsigned int x, unsigned int y) : x(x), y(y) {}
	~Vector2u() {}
	std::string to_string();
	bool operator==(const Vector2u& other) const { return (x == other.x) && (y == other.y); }
	bool operator==(const int& other) const { return (x == other) && (y == other); }
	bool operator!=(const Vector2u& other) const { return !(*this == other); }
	Vector2u operator+(const Vector2u& other) const { return Vector2u(x + other.x, y + other.y); }
	Vector2u operator-(const Vector2u& other) const { return Vector2u(std::abs(int(x - other.x)), std::abs(int(y - other.y))); }
	friend std::ostream& operator<<(std::ostream&, const Vector2u&);
};

#endif // _VECTOR2_HPP_