#include "maze.h"

bool Maze::isWalkable(const Vec &loc) const {
	return cells_[loc.y][loc.x]->isWalkable();
}
bool Maze::isInBound(const Vec &loc) const {
	return loc.x >= 0 && loc.y >= 0
			&& loc.x < width_ && loc.y < height_;
}
int Maze::getHeight() const {
	return height_;
}
int Maze::getWidth() const {
	return width_;
}
const Vec &Maze::getRobotLocation() const {
	return robot_loc_;
}
bool Maze::FreeSpaceCell::isWalkable() const {
	return true;
}
const Maze::FreeSpaceCell &Maze::FreeSpaceCell::getInstance() {
	static const FreeSpaceCell instance;
	return instance;
}
bool Maze::WallCell::isWalkable() const {
	return false;
}
const Maze::WallCell &Maze::WallCell::getInstance() {
	static const WallCell instance;
	return instance;
}