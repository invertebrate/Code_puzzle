#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

class Vector2
{
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
		bool operator==(const Vector2 &other);
		float operator*(const Vector2 &other);
};

class Vector2int
{
	  public:
		int x;
		int y;
		Vector2int(int x, int y);
		Vector2int();
		Vector2int(const Vector2int &);
		Vector2int operator+(const Vector2int &other);
		Vector2int operator-(const Vector2int &other);
		Vector2int operator=(const Vector2int &other);
		bool operator<=(const Vector2int &other);
		bool operator>=(const Vector2int &other);
		bool operator==(const Vector2int &other);
		int operator*(const Vector2int &other);
};
#endif