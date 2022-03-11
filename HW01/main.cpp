#include <bits/stdc++.h>

// using namespace std;

class Orientation {
public:
	enum class EOrientation { FRONT, RIGHT, BACK, LEFT };
	Orientation(EOrientation orientation): value_(static_cast<int>(orientation)) {};
	Orientation &operator=(const Orientation &rhs) {
		this->value_ = rhs.value_;
	}
	Orientation &operator++() {
		value_ = (value_+1)%4;
		return *this;
	}
	Orientation &operator--() {
		value_ = (value_+3)%4;
		return *this;
	}
	const EOrientation &getOrientation() const {
		return static_cast<EOrientation>(value_);
	}
private:
	int value_;
};

class Direction {
public:
	enum class EDirection { UP, RIGHT, DOWN, LEFT };
	Direction(EDirection direction): value_(static_cast<int>(direction)) {};
	Direction &operator=(const Direction &rhs) {
		this->value_ = rhs.value_;
	}
	Direction &operator++() {
		value_ = (value_+1)%4;
		return *this;
	}
	Direction &operator--() {
		value_ = (value_+3)%4;
		return *this;
	}
	const EDirection &getDirection() const {
		return static_cast<EDirection>(value_);
	}
private:
	int value_;
};


class Vec {
public:
	int x, y;
	Vec(): x(0), y(0) {}
	Vec(int x, int y): x(x), y(y) {}
	bool operator==(const Vec &rhs) { return (this->x == rhs.x && this->y == rhs.y); }
	bool operator!=(const Vec &rhs) { return (this->x != rhs.x && this->y == rhs.y); }
	Vec operator+(const Vec &rhs) { return Vec(this->x+rhs.x, this->y+rhs.y); }
	Vec operator-(const Vec &rhs) { return Vec(this->x-rhs.x, this->y-rhs.y); }
};

class ICell {
public:
	ICell() {}
	ICell(int x, int y): loc_(x, y) {}
	virtual bool canWalk();
	const Vec getLocation() { return loc_; };
private:
	Vec loc_;
};

class IMaze {

};

class Robot {
public:
	Robot(): loc_(0, 0), dir_(Direction::EDirection::UP) {}
	Robot(int x, int y): loc_(x, y), dir_(Direction::EDirection::UP) {}
	Robot(int x, int y, const Direction &dir): loc_(x, y), dir_(dir) {}
	Robot(const Vec &loc, const Direction &dir): loc_(loc), dir_(dir) {}
	Vec getPos() { return loc_; }
	Direction getDir() { return dir_; }
	void setDir(const Direction &dir) { this->dir_ = dir; }
	void turn(const Orientation &orient) {
		switch(orient.getOrientation()) {
		case Orientation::EOrientation::FRONT: break;
		case Orientation::EOrientation::RIGHT: ++dir_; break;
		case Orientation::EOrientation::BACK: ++++dir_;break;
		case Orientation::EOrientation::LEFT: --dir_; break;
		}
	}
	void move(const Orientation orient = Orientation::FRONT) {
		auto tmp_dir = dir_.rotate(orient);
		
	}
private:
	Vec loc_;
	Direction dir_;
};

int main() {
	int w;
	int h;
	cin >> w >> h; cin.ignore();
	long long n;
	cin >> n; cin.ignore();
	for (int i = 0; i < h; i++) {
		string line;
		getline(cin, line);
	}
	Robot rob(1, 2);
	Direction dir = Direction::UP;
	dir = dir.rotate(Orientation::RIGHT);
	// Write an answer using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;

	cout << "answer" << endl;
}