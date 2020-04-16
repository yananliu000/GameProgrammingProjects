//VECTOR2 H
#ifndef MYVECTOR2_H
#define MYVECTOR2_H
#include <math.h>

class MyVector2
{
public:
	float x;
	float y;

	MyVector2() = default;
	MyVector2(float xValue, float yValue) : x(xValue), y(yValue) { }
	MyVector2(const MyVector2& v) : x(v.x), y(v.y) { }
	MyVector2(const MyVector2* v) : x(v->x), y(v->y) { }
	
	~MyVector2() = default;

	inline MyVector2& MyVector2::operator = (const MyVector2& v) { x = v.x; y = v.y; return *this; }
	inline MyVector2& MyVector2::operator = (const float& f) { x = f; y = f; return *this; }
	inline MyVector2& MyVector2::operator - (void) { x = -x; y = -y; return *this; }
	inline bool MyVector2::operator == (const MyVector2& v) const { return (x == v.x) && (y == v.y); }
	inline bool MyVector2::operator != (const MyVector2& v) const { return (x != v.x) || (y != v.y); }

	inline const MyVector2 MyVector2::operator + (const MyVector2& v) const { return MyVector2(x + v.x, y + v.y); }
	inline const MyVector2 MyVector2::operator - (const MyVector2& v) const { return MyVector2(x - v.x, y - v.y); }
	inline const MyVector2 MyVector2::operator * (const MyVector2& v) const { return MyVector2(x * v.x, y * v.y); }
	inline const MyVector2 MyVector2::operator / (const MyVector2& v) const { return MyVector2(x / v.x, y / v.y); }

	inline MyVector2& MyVector2::operator += (const MyVector2& v) { x += v.x; y += v.y; return *this; }
	inline MyVector2& MyVector2::operator -= (const MyVector2& v) { x -= v.x; y -= v.y; return *this; }
	inline MyVector2& MyVector2::operator *= (const MyVector2& v) { x *= v.x; y *= v.y; return *this; }
	inline MyVector2& MyVector2::operator /= (const MyVector2& v) { x /= v.x; y /= v.y; return *this; }
	
	inline const MyVector2 MyVector2::operator + (float v) const { return MyVector2(x + v, y + v); }
	inline const MyVector2 MyVector2::operator - (float v) const { return MyVector2(x - v, y - v); }
	inline const MyVector2 MyVector2::operator * (float v) const { return MyVector2(x * v, y * v); }
	inline const MyVector2 MyVector2::operator / (float v) const { return MyVector2(x / v, y / v); }

	inline MyVector2& MyVector2::operator += (float v) { x += v; y += v; return *this; }
	inline MyVector2& MyVector2::operator -= (float v) { x -= v; y -= v; return *this; }
	inline MyVector2& MyVector2::operator *= (float v) { x *= v; y *= v; return *this; }
	inline MyVector2& MyVector2::operator /= (float v) { x /= v; y /= v; return *this; }

	float MyVector2::LengthSquared() const { return x * x + y * y; }
	float MyVector2::Dot(const MyVector2& v) const { return x * v.x + y * v.y; }
	float MyVector2::Cross(const MyVector2& v) const { return x * v.y + y * v.x; }
};
#endif