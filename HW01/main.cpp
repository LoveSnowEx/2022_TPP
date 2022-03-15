#include <bits/stdc++.h>

// using namespace std;

// a 2d vector for math. not std::vector
class Vec {
public:
	int x, y;
	Vec() = default;
	Vec(int x, int y): x(x), y(y) {}
	Vec(const Vec &rhs) = default;
	Vec &operator=(const Vec &rhs) = default;
	bool operator==(const Vec &rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
	bool operator!=(const Vec &rhs) const { return (this->x != rhs.x && this->y == rhs.y); }
	bool operator<(const Vec &rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
	Vec operator+(const Vec &rhs) const { return Vec(this->x+rhs.x, this->y+rhs.y); }
	Vec operator-(const Vec &rhs) const { return Vec(this->x-rhs.x, this->y-rhs.y); }
	Vec &operator+=(const Vec &rhs) { return *this = *this + rhs; }
	Vec &operator-=(const Vec &rhs) { return *this = *this - rhs; }
};

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


class Maze: public IMaze {
public:
	// initialization
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
	virtual bool isWalkable(const Vec &loc) const override {
		return cells_[loc.x][loc.y]->isWalkable();
	}
	virtual bool isInBound(const Vec &loc) const override {
		return loc.x >= 0 && loc.y >= 0
				&& loc.x < height_ && loc.y < width_;
	}
	virtual int getHeight() const override {
		return height_;
	}
	virtual int getWidth() const override {
		return width_;
	}
	virtual const Vec &getRobotLocation() const override {
		return robot_loc_;
	}
private:
	int height_, width_;
	Vec robot_loc_;
	std::vector<std::vector<const IWalkableCell*>> cells_;  // 2d std::vector of pointer to IWalkableCell
	static constexpr char WALL = '#', ROBOT = 'O';
	class FreeSpaceCell: public IWalkableCell {  // singleton free space cell
	public:
		virtual bool isWalkable() const override {
			return true;
		}
		static const FreeSpaceCell &getInstance() {
			static const FreeSpaceCell instance;
			return instance;
		}
	};
	class WallCell: public IWalkableCell {  // singleton wall cell
	public:
		virtual bool isWalkable() const override {
			return false;
		}
		static const WallCell &getInstance() {
			static const WallCell instance;
			return instance;
		}
	};
};


class Robot {
public:
	enum class EDirection {UP, RIGHT, DOWN, LEFT};
	enum class EOrientation {FRONT, RIGHT, BACK, LEFT};
	class Status {
	public:
		Vec loc;
		EDirection dir;
		Status(Vec loc, EDirection dir): loc(loc), dir(dir) {}
		bool operator<(const Status &rhs) const {
			return (loc == rhs.loc ? dir < rhs.dir : loc < rhs.loc);
		}
		Status &operator=(const Status &) = default;
	};
	Robot() = default;
	void loadMaze(const IMaze *maze) { maze_ = maze; }
	const Vec &getLocation() const { return loc_; }
	const EDirection &getDirection() const { return dir_; }
	const int &getStep() const { return step_; }
	const auto &getHistory() const { return history_; }
	const auto &getPath() const { return path_; }
	const Status getStatus() const { return {loc_, dir_}; }
	const Status getStatus(int step) const { return path_[step]; }
	void setLocation(const Vec &loc) { loc_ = loc; }
	void setDirection(const EDirection &dir) { dir_ = dir; }
	void setStep(int step) { step_ = step; }
	void setStaus(const Status &status) { loc_ = status.loc, dir_ = status.dir; }
	bool boundFront() const {
		return !maze_->isInBound(loc_+frontVec());
	}
	bool wallFront() const {
		return !maze_->isWalkable(loc_+frontVec());
	}
	void moveForward() {
		loc_ += frontVec();
	}
	void turnRight() {
		dir_ = static_cast<EDirection>((static_cast<int>(dir_)+1)%4);
	}
	void turnLeft() {
		dir_ = static_cast<EDirection>((static_cast<int>(dir_)+3)%4);
	}
	bool hasVisited() const {
		return history_.count(getStatus());
	}
	void logStatus() {
		history_.emplace(getStatus(), step_);
		path_.emplace_back(getStatus());
	}
	// user can solve by custom function
	template<typename Func>
	auto solve(Func func) {
		step_ = 0;
		loc_ = maze_->getRobotLocation();
		dir_ = EDirection::UP;
		history_.clear();
		path_.clear();
		return func();
	}
private:
	int step_;
	Vec loc_;
	EDirection dir_;
	const IMaze *maze_;
	std::map<Status, int> history_;  // get step by status from history
	std::vector<Status> path_;  // get status by step
	const Vec &frontVec() const {  // the front vector of robot
		static const Vec UP(-1, 0), RIGHT(0, 1), DOWN(1, 0), LEFT(0, -1);
		switch(dir_) {
		case EDirection::UP: return UP; break;
		case EDirection::RIGHT: return RIGHT; break;
		case EDirection::DOWN: return DOWN; break;
		case EDirection::LEFT: return LEFT; break;
		}
		return UP;
	}
};

int main() {
	freopen("in.txt", "r", stdin);
	int w, h;
	long long n;
	std::cin >> w >> h >> n; std::cin.ignore();

	std::vector<std::string> lines(h);
	for (auto &line: lines) std::getline(std::cin, line);

	Maze maze(lines);
	Robot robot;
	robot.loadMaze(&maze);

	auto res = robot.solve([&n, &robot]() {
		while(robot.getStep() < n) {
			// turn right if can not walk forward
			while(robot.boundFront() || robot.wallFront()) robot.turnRight();
			// if status has appeared
			if(robot.hasVisited()) {
				// reduce loop step
				auto cur = robot.getStep(), pre = robot.getHistory().at(robot.getStatus());
				n = pre + (n-pre) % (cur-pre);
				robot.setStaus(robot.getStatus(n));
				return robot.getLocation();
			}
			robot.logStatus();
			robot.moveForward();
			robot.setStep(robot.getStep()+1);
		}
		return robot.getLocation();
	});
	
	// because the result is row major, the output should be reverse
	std::cout << res.y << ' ' << res.x << std::endl;
}