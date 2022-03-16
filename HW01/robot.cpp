#include "robot.h"

Robot::Robot(): loc_(), dir_(EDirection::UP), maze_(nullptr) {};
const Vec &Robot::getLocation() const { return loc_; }
const Robot::EDirection &Robot::getDirection() const { return dir_; }
void Robot::setLocation(const Vec &loc) { loc_ = loc; }
void Robot::setDirection(const EDirection &dir) { dir_ = dir; }
void Robot::loadMaze(const IMaze *maze) {
	maze_ = maze;
	loc_ = maze_->getRobotLocation();
}
bool Robot::boundFront() const {
	return !maze_->isInBound(loc_+frontVec());
}
bool Robot::wallFront() const {
	return !maze_->isWalkable(loc_+frontVec());
}
void Robot::moveForward() {
	loc_ += frontVec();
}
void Robot::turnRight() {
	dir_ = static_cast<EDirection>((static_cast<int>(dir_)+1)%4);
}
void Robot::turnLeft() {
	dir_ = static_cast<EDirection>((static_cast<int>(dir_)+3)%4);
}
const Vec &Robot::frontVec() const {
	static const Vec UP(0, -1), RIGHT(1, 0), DOWN(0, 1), LEFT(-1, 0);
	switch(dir_) {
	case EDirection::UP: return UP; break;
	case EDirection::RIGHT: return RIGHT; break;
	case EDirection::DOWN: return DOWN; break;
	case EDirection::LEFT: return LEFT; break;
	}
	return UP;
}
