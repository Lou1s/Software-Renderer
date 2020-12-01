#pragma once
template <class T>
class Vec2 {
private:

public:
	T x;
	T y;
	Vec2() : x(0.0), y(0.0) {};
	Vec2(T x_val, T y_val) : x(x_val), y(y_val) {};
	Vec2(Vec2& other) : x(other.x), y(other._y) {};
};