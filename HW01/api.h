#pragma once

#include "vec.h"

// interface of cell that walkable
class IWalkableCell {
public:
	virtual bool isWalkable() const = 0;
};

// interface of maze
class IMaze {
public:
	virtual bool isWalkable(const Vec &loc) const = 0;
	virtual bool isInBound(const Vec &loc) const = 0;
	virtual int getHeight() const = 0;
	virtual int getWidth() const = 0;
	virtual const Vec &getRobotLocation() const = 0;
};