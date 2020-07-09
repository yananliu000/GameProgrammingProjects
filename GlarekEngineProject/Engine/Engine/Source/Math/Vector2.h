#pragma once
/** \file Vector2.h */
/** TODO: File Purpose */
// Created by Billy Graban

/** \class Vector2 */
/** TODO: Class Purpose */
#define DLLEXP __declspec(dllexport)

template <class T> class Vector2
{
public:
	T x;
	T y;

	DLLEXP Vector2(T xValue, T yValue) { x = xValue; y = yValue; };
	DLLEXP Vector2() {}
	DLLEXP ~Vector2() {}
	DLLEXP Vector2 const operator+ (Vector2 const& rhs) const { Vector2 result(*this); return result += rhs; }
	DLLEXP Vector2 const operator- (Vector2 const& rhs) const { Vector2 result(*this); return result -= rhs; }
	DLLEXP Vector2 const operator* (T scale) const { Vector2 result(*this); return result *= scale; }
	DLLEXP Vector2& operator+=(Vector2 const& v) { x += v.x; y += v.y; return *this; }
	DLLEXP Vector2& operator-=(Vector2 const& v) { x -= v.x; y -= v.y; return *this; }
	DLLEXP Vector2& operator*=(T scale) { x *= scale; y *= scale; return *this; }
	DLLEXP T Dot(Vector2 const& rhs) { return (this->x * rhs.x) + (this->y * rhs.y); }
};