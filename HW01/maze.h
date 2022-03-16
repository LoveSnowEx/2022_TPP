#pragma once

#include <string>
#include <vector>
#include <map>
#include "api.h"

class Maze: public IMaze {
public:
	// initialization, templates should be implemented in the header file
	template<typename T>
	Maze(const T &src)
		: height_(src.size())
		, width_(height_ ? src[0].size() : 0)
		, cells_(height_, std::vector<const IWalkableCell*>(width_)) {
		for(int y = 0; y < height_; y++) {
			for(int x = 0; x < width_; x++) {
				switch(src[y][x]) {  // switch char at (x, y) to set cell
				case WALL: cells_[y][x] = &WallCell::getInstance(); break;
				case ROBOT: robot_loc_ = {x, y}; [[fallthrough]];
				default: cells_[y][x] = &FreeSpaceCell::getInstance(); break;
				}
			}
		}
	}
	virtual bool isWalkable(const Vec &loc) const override;
	virtual bool isInBound(const Vec &loc) const override;
	virtual int getHeight() const override;
	virtual int getWidth() const override;
	virtual const Vec &getRobotLocation() const override;
private:
	int height_, width_;
	Vec robot_loc_;
	std::vector<std::vector<const IWalkableCell*>> cells_;  // 2d std::vector of pointer to IWalkableCell
	static constexpr char WALL = '#', ROBOT = 'O';
	class FreeSpaceCell: public IWalkableCell {  // singleton free space cell
	public:
		virtual bool isWalkable() const override;
		static const FreeSpaceCell &getInstance();
	};
	class WallCell: public IWalkableCell {  // singleton wall cell
	public:
		virtual bool isWalkable() const override;
		static const WallCell &getInstance();
	};
};