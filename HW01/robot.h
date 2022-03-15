#pragma once

#include <vector>
#include <map>
#include "api.h"

class Robot {
public:
	enum class EDirection {UP, RIGHT, DOWN, LEFT};
	enum class EOrientation {FRONT, RIGHT, BACK, LEFT};
	class Status {
	public:
		Vec loc;
		EDirection dir;
		Status(Vec loc, EDirection dir);
		Status &operator=(const Status &);
		bool operator<(const Status &rhs) const;
	};
	Robot();
	const Vec &getLocation() const;
	const EDirection &getDirection() const;
	const int &getStep() const;
	const std::map<Status, int> &getHistory() const;
	const std::vector<Status> &getPath() const;
	const Status getStatus() const;
	const Status getStatus(int step) const;
	void setLocation(const Vec &loc);
	void setDirection(const EDirection &dir);
	void setStep(int step);
	void setStaus(const Status &status);
	void loadMaze(const IMaze *maze);
	bool boundFront() const;
	bool wallFront() const;
	void moveForward();
	void turnRight();
	void turnLeft();
	bool hasVisited() const;
	void logStatus();
private:
	Vec loc_;
	EDirection dir_;
	const IMaze *maze_;
	int step_;
	std::map<Status, int> history_;  // get step by status from history
	std::vector<Status> path_;  // get status by step
	const Vec &frontVec() const;  // the front vector of robot
};