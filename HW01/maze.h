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
		for(int i = 0; i < height_; i++) {
			for(int j = 0; j < width_; j++) {
				switch(src[i][j]) {
				case WALL: cells_[i][j] = &WallCell::getInstance(); break;
				case ROBOT: robot_loc_ = {i, j}; [[fallthrough]];
				default: cells_[i][j] = &FreeSpaceCell::getInstance(); break;
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