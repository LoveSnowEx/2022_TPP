#include "api.h"
#include <bits/stdc++.h>

using namespace std;

class PathFinding{
public:
	static constexpr size_t WIDTH = 9, HEIGHT = 5, MAX_IDX = WIDTH*HEIGHT;
	static constexpr int MAX_DISTANCE = 1000;
	static constexpr array<array<array<int, MAX_IDX>, MAX_IDX>, MAX_IDX> getDistance() {  // distance[partner][from][to]
		array<array<array<int, MAX_IDX>, MAX_IDX>, MAX_IDX> distance = {};
		const array<int, MAX_DISTANCE> tablesIdx = {10, 11 ,12 ,13, 15, 16, 19, 22, 25, 28 ,29, 31, 32, 33, 34};
		bitset<MAX_DISTANCE> isTable;
		for(const auto &tableIdx: tablesIdx) isTable[tableIdx] = true;
		for(size_t i = 0; i < MAX_IDX; ++i) {
			for(size_t j = 0; j < MAX_IDX; ++j) {
				for(size_t k = 0; k < MAX_IDX; ++k) {
					distance[i][j][k] = MAX_DISTANCE;
					// j or k is partner or table
					if(j == i || k == i  // is partner
						|| isTable[j] || isTable[k] ) {  // is table
						continue;
					}
					int x1 = j%WIDTH, y1 = j/WIDTH, x2 = k%WIDTH, y2 = k/WIDTH, dis = abs(x2-x1) + abs(y2-y1);
					if(dis <= 1) {
						distance[i][j][k] = dis;
					}
				}
			}
		}
		for(size_t i = 0; i < MAX_IDX; ++i) {
			if(isTable[i]) continue;
			for(size_t l = 0; l < MAX_IDX; ++l) {
				if(isTable[l]) continue;
				for(size_t j = 0; j < MAX_IDX; ++j) {
					if(isTable[j]) continue;
					for(size_t k = 0; k < MAX_IDX; ++k) {
						if(isTable[k]) continue;
						if(distance[i][j][k] > distance[i][j][l] + distance[i][l][k]) {
							distance[i][j][k] = distance[i][j][l] + distance[i][l][k];
						}
					}
				}
			}
		}
		return distance;
	}
};


int main() {
	freopen("in.txt", "r", stdin);
    int num_all_customers;
    cin >> num_all_customers; cin.ignore();
    for (int i = 0; i < num_all_customers; i++) {
        string customer_item; // the food the customer is waiting for
        int customer_award; // the number of points awarded for delivering the food
        cin >> customer_item >> customer_award; cin.ignore();
    }
	vector<string> kitchen_lines(7);
    for (int i = 0; i < 7; i++) {
        getline(cin, kitchen_lines[i]);
    }
	const auto &&distance = PathFinding::getDistance();

    // game loop
	return 0;
    while (1) {
        int turns_remaining;
        cin >> turns_remaining; cin.ignore();
        int player_x;
        int player_y;
        string player_item;
        cin >> player_x >> player_y >> player_item; cin.ignore();
        int partner_x;
        int partner_y;
        string partner_item;
        cin >> partner_x >> partner_y >> partner_item; cin.ignore();
        int num_tables_with_items; // the number of tables in the kitchen that currently hold an item
        cin >> num_tables_with_items; cin.ignore();
        for (int i = 0; i < num_tables_with_items; i++) {
            int table_x;
            int table_y;
            string item;
            cin >> table_x >> table_y >> item; cin.ignore();
        }
        string oven_contents; // ignore until wood 1 league
        int oven_timer;
        cin >> oven_contents >> oven_timer; cin.ignore();
        int num_customers; // the number of customers currently waiting for food
        cin >> num_customers; cin.ignore();
        for (int i = 0; i < num_customers; i++) {
            string customer_item;
            int customer_award;
            cin >> customer_item >> customer_award; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // MOVE x y
        // USE x y
        // WAIT
		size_t playerIdx = (player_y-1)*9+(player_x-1);
		size_t partnerIdx = (partner_y-1)*9+(partner_x-1);
		const auto &row = distance[partnerIdx][playerIdx];
		cerr << "table: " << partnerIdx << '\n' << endl;
		int cnt = 0;
		for(const auto &element: row) {
			int x = cnt%9, y = cnt/9;
			cerr << "distance to " << x+1 << " " << y+1 << " is " << element << endl;
            cnt++;
		}
        cout << "WAIT" << endl;
    }
}