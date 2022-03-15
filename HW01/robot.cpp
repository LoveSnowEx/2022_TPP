#include "robot.h"

Robot::Status::Status(Vec loc, EDirection dir): loc(loc), dir(dir) {}
bool Robot::Status::operator<(const Status &rhs) const {
	return (loc == rhs.loc ? dir < rhs.dir : loc < rhs.loc);
}
Robot::Status &Robot::Status::operator=(const Status &) = default;
Robot::Robot(): loc_(), dir_(EDirection::UP), maze_(nullptr), step_(0) {};
const Vec &Robot::getLocation() const { return loc_; }
const Robot::EDirection &Robot::getDirection() const { return dir_; }
const int &Robot::getStep() const { return step_; }
const std::map<Robot::Status, int> &Robot::getHistory() const { return history_; }
const std::vector<Robot::Status> &Robot::getPath() const { return path_; }
const Robot::Status Robot::getStatus() const { return {loc_, dir_}; }
const Robot::Status Robot::getStatus(int step) const { return path_[step]; }
void Robot::setLocation(const Vec &loc) { loc_ = loc; }
void Robot::setDirection(const EDirection &dir) { dir_ = dir; }
void Robot::setStep(int step) { step_ = step; }
void Robot::setStaus(const Status &status) { loc_ = status.loc, dir_ = status.dir; }
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
bool Robot::hasVisited() const {
	return history_.count(getStatus());
}
void Robot::logStatus() {
	history_.emplace(getStatus(), step_);
	path_.emplace_back(getStatus());
}
const Vec &Robot::frontVec() const {
	static const Vec UP(-1, 0), RIGHT(0, 1), DOWN(1, 0), LEFT(0, -1);
	switch(dir_) {
	case EDirection::UP: return UP; break;
	case EDirection::RIGHT: return RIGHT; break;
	case EDirection::DOWN: return DOWN; break;
	case EDirection::LEFT: return LEFT; break;
	}
	return UP;
}