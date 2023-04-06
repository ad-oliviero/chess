#ifndef _VECTOR2_HPP_
#define _VECTOR2_HPP_

#include <string>

template <typename T>
class Vector2 {
public:
	T x;
	T y;

	Vector2() : Vector2(0, 0) {}
	Vector2(T x, T y) : x(x), y(y) {}
	~Vector2() {}
	std::string to_string();
	bool operator==(const Vector2& other) const { return (x == other.x) && (y == other.y); }
	bool operator==(const int& other) const { return (x == other) && (y == other); }
	bool operator!=(const Vector2& other) const { return !(*this == other); }
	Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
	Vector2 operator-(const Vector2& other) const { return Vector2(std::abs(int(x - other.x)), std::abs(int(y - other.y))); }
	friend std::ostream& operator<<(std::ostream&, const Vector2<unsigned int>&);
};

#endif // _VECTOR2_HPP_