#pragma once

#include <vector>
#include <map>
#include "api.h"

class Robot {
public:
	enum class EDirection {UP, RIGHT, DOWN, LEFT};
	Robot();
	const Vec &getLocation() const;
	const EDirection &getDirection() const;
	void setLocation(const Vec &loc);
	void setDirection(const EDirection &dir);
	void loadMaze(const IMaze *maze);
	bool boundFront() const;
	bool wallFront() const;
	void moveForward();
	void turnRight();
	void turnLeft();
private:
	Vec loc_;
	EDirection dir_;
	const IMaze *maze_;
	const Vec &frontVec() const;  // the front vector of robot
};
