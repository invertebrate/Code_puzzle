#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class Vector2 {
      public:
	float x;
	float y;
	Vector2(float x, float y);
	Vector2();
	Vector2(const Vector2 &);
	Vector2 operator+(const Vector2 &other);
	Vector2 operator-(const Vector2 &other);
	Vector2 operator=(const Vector2 &other);
	bool operator<=(const Vector2 &other);
	bool operator>=(const Vector2 &other);
	float operator*(const Vector2 &other);
};
#endif