#pragma once

// a 2d vector for math. not std::vector
class Vec {
public:
	int x, y;
	Vec();
	Vec(int x, int y);
	Vec(const Vec &rhs);
	Vec &operator=(const Vec &rhs);
	bool operator==(const Vec &rhs) const;
	bool operator!=(const Vec &rhs) const;
	bool operator<(const Vec &rhs) const;
	Vec operator+(const Vec &rhs) const;
	Vec operator-(const Vec &rhs) const;
	Vec &operator+=(const Vec &rhs);
	Vec &operator-=(const Vec &rhs);
};