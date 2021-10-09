#include "vector.h"
#include "code_puzzle.h"

Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(const Vector2 &other) {
	this->x = other.x;
	this->y = other.y;
}
Vector2 Vector2::operator+(const Vector2 &other) {
	Vector2 res;
	res.x = this->x + other.x;
	res.y = this->y + other.y;
	return (res);
}
Vector2 Vector2::operator-(const Vector2 &other) {
	Vector2 res;
	res.x = this->x - other.x;
	res.y = this->y - other.y;
	return (res);
}
Vector2 Vector2::operator=(const Vector2 &other) {
	x = other.x;
	y = other.y;
	return (*this);
}
bool Vector2::operator<=(const Vector2 &other) {
	if (this->x <= other.x && this->y <= other.y)
		return (true);
	else
		return (false);
}
bool Vector2::operator>=(const Vector2 &other) {
	if (this->x >= other.x && this->y >= other.y)
		return (true);
	else
		return (false);
}
float Vector2::operator*(const Vector2 &other) {
	return (sqrt(this->x * other.x + this->y * other.y));
}