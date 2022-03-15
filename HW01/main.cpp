#include <bits/stdc++.h>
#include "robot.h"
#include "maze.h"

int main() {
	// freopen("in.txt", "r", stdin);
	int w, h;
	long long n;
	std::cin >> w >> h >> n; std::cin.ignore();

	std::vector<std::string> lines(h);
	for (auto &line: lines) std::getline(std::cin, line);
	
	Maze maze(lines);
	Robot robot;
	robot.loadMaze(&maze);

	auto res = [&n, &robot]() mutable {
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
	}();
	
	// because the result is row major, the output should be reverse
	std::cout << res.y << ' ' << res.x << std::endl;
}