#include <iostream>
#include "robot.h"
#include "maze.h"

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

	auto &&res = [&n, &robot]() mutable {
		int step = 0;
		std::map<std::pair<Vec, Robot::EDirection>, int> history;  // get step by status from history
		std::vector<std::pair<Vec, Robot::EDirection>> path;  // get status by step
		while(step < n) {
			// turn right if can not walk forward
			while(robot.boundFront() || robot.wallFront()) robot.turnRight();
			
			// make status
			auto &&status = std::make_pair(robot.getLocation(), robot.getDirection());

			// found if status has appeared in history
			if(auto &&found = history.find(status); found != history.end()) {
				// reduce loop step
				int pre = found->second;
				n = pre + (n-pre) % (step-pre);
				return path[n].first;
			}
			history.emplace(status, step);
			path.emplace_back(status);
			robot.moveForward();
			step++;
		}
		return robot.getLocation();
	}();

	std::cout << res.x << ' ' << res.y << std::endl;
}
