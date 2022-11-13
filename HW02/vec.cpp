#include "vec.h"

Vec::Vec(): x(0), y(0) {};
Vec::Vec(int x, int y): x(x), y(y) {}
Vec::Vec(const Vec &rhs): x(rhs.x), y(rhs.y) {};
Vec &Vec::operator=(const Vec &rhs) = default;
bool Vec::operator==(const Vec &rhs) const { return (x == rhs.x && y == rhs.y); }
bool Vec::operator!=(const Vec &rhs) const { return (x != rhs.x && y == rhs.y); }
bool Vec::operator<(const Vec &rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
Vec Vec::operator+(const Vec &rhs) const { return Vec(x+rhs.x, y+rhs.y); }
Vec Vec::operator-(const Vec &rhs) const { return Vec(x-rhs.x, y-rhs.y); }
Vec &Vec::operator+=(const Vec &rhs) { return *this = *this + rhs; }
Vec &Vec::operator-=(const Vec &rhs) { return *this = *this - rhs; }
