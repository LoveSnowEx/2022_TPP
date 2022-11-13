#pragma once

#include<bits/stdc++.h>

class Vec {
public:
	int x, y;
	Vec(): x(0), y(0) {};
	Vec(int x, int y): x(x), y(y) {}
	Vec(const Vec &rhs): x(rhs.x), y(rhs.y) {};
	Vec &operator=(const Vec &rhs) = default;
	bool operator==(const Vec &rhs) const { return (x == rhs.x && y == rhs.y); }
	bool operator!=(const Vec &rhs) const { return (x != rhs.x || y != rhs.y); }
	bool operator<(const Vec &rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
	Vec operator+(const Vec &rhs) const { return Vec(x+rhs.x, y+rhs.y); }
	Vec operator-(const Vec &rhs) const { return Vec(x-rhs.x, y-rhs.y); }
	Vec &operator+=(const Vec &rhs) { return *this = *this + rhs; }
	Vec &operator-=(const Vec &rhs) { return *this = *this - rhs; }
	double length() const { return sqrt(x*x+y*y); }
	double distance(const Vec &rhs) const { return (*this - rhs).length(); }
};