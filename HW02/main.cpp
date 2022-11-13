#include "lib.h"
#include "vec.h"
#include "kitchen.h"

constexpr bool readFromText = true;

int main() {
	if(readFromText) freopen("in.txt", "r", stdin);
	int num_all_customers;
	cin >> num_all_customers; cin.ignore();
	for (int i = 0; i < num_all_customers; i++) {
		string customer_item; // the food the customer is waiting for
		int customer_award; // the number of points awarded for delivering the food
		cin >> customer_item >> customer_award; cin.ignore();
	}
	
	shared_ptr<Window> window = make_shared<Window>();
	vector<shared_ptr<Maker>> makers;
	vector<shared_ptr<Container>> tables;
	shared_ptr<Container> dishWasher = make_shared<Container>();
	shared_ptr<Container> blueberryCrate = make_shared<Container>();
	shared_ptr<Container> iceCreamCrate = make_shared<Container>();
	shared_ptr<Container> strawberriesCrate = make_shared<Container>();
	shared_ptr<Container> doughCrate = make_shared<Container>();
	shared_ptr<ChoppingBoard> choppingBoard = make_shared<ChoppingBoard>();
	shared_ptr<Oven> oven = make_shared<Oven>();

	blueberryCrate->items = Items(EFood::BLUEBERRIES);
	iceCreamCrate->items = Items(EFood::ICE_CREAM);
	strawberriesCrate->items = Items(EFood::STRAWBERRIES);
	doughCrate->items = Items(EFood::DOUGH);
	choppingBoard->recipes = {
		{Items(EFood::CHOPPED_DOUGH), Items(EFood::DOUGH)},
		{Items(EFood::CHOPPED_STRAWBERRIES), Items(EFood::STRAWBERRIES)},
	};
	oven->recipes = {
		{Items(EFood::CROISSANT), Items(EFood::DOUGH)},
		{Items(EFood::TART), Items(EFood::RAW_TART)},
	};
	makers.emplace_back(choppingBoard);
	makers.emplace_back(oven);

	for (int i = 0; i < 7; i++) {
		string kitchen_line;
		getline(cin, kitchen_line);
		cerr << kitchen_line << endl;
		for(int j = 0; j < 11; j++) {
			auto &&loc = Vec(j, i);
			shared_ptr<Container> table;
			shared_ptr<Maker> maker;
			switch(kitchen_line[j]) {
			case '.': break;
			case '#':
				table = make_shared<Container>();
				table->loc = loc;
				tables.emplace_back(table);
				break;
			case 'D': dishWasher->loc = loc; break;
			case 'W': window->loc = loc; break;
			case 'B': blueberryCrate->loc = loc; break;
			case 'I': iceCreamCrate->loc = loc; break;
			case 'S': strawberriesCrate->loc = loc; break;
			case 'H': doughCrate->loc = loc; break;
			case 'C': choppingBoard->loc = loc; break;
			case 'O': oven->loc = loc; break;
			}
		}
	}

	Kitchen kitchen;
	kitchen.window = window;
	kitchen.dishWasher = dishWasher;
	kitchen.containers.insert(kitchen.containers.end(), tables.begin(), tables.end());
	kitchen.containers.emplace_back(dishWasher);
	kitchen.containers.emplace_back(blueberryCrate);
	kitchen.containers.emplace_back(iceCreamCrate);
	kitchen.containers.emplace_back(strawberriesCrate);
	kitchen.containers.emplace_back(doughCrate);
	kitchen.containers.emplace_back(oven);
	kitchen.mergeRecipes = {
		{Items(EFood::RAW_TART), make_pair(Items(EFood::CHOPPED_DOUGH), Items(EFood::BLUEBERRIES))},
	};
	
	for(auto &maker: makers) {
		if(!maker) continue;
		// cerr << "maker:"; maker->print();
		for(auto &recipe: maker->recipes) {
			kitchen.makers[recipe.first] =  maker;
			// cerr << "kichen maker add:" << endl;
			// cerr << "product:"; recipe.first.print();
			// cerr << "material:"; recipe.second.print();
		}
	}

	// game loop
	while (1) {
		int dishCnt = 3;

		int turns_remaining;
		cin >> turns_remaining; cin.ignore();
		cerr << "turns remaining " << turns_remaining << endl;

		if(turns_remaining < 0) break;

		int player_x, player_y;
		string player_item;
		cin >> player_x >> player_y >> player_item; cin.ignore();
		cerr << "player " << player_x << ' ' << player_y << endl << "player items: " << player_item << endl;

		Chef player;
		player.loc = Vec(player_x, player_y);
		player.items = str2Items(player_item);
		// player.items.print();

		int partner_x, partner_y;
		string partner_item;
		cin >> partner_x >> partner_y >> partner_item; cin.ignore();
		cerr << "partner " << partner_x << ' ' << partner_y << endl << "partner items: " << partner_item << endl;

		Chef partner;
		partner.loc = Vec(partner_x, partner_y);
		partner.items = str2Items(partner_item);
		// partner.items.print();

		// cerr << "update tables " << endl;
		int num_tables_with_items; // the number of tables in the kitchen that currently hold an item
		cin >> num_tables_with_items; cin.ignore();
		for(auto &table: tables) table->items.clear();
		for (int i = 0; i < num_tables_with_items; i++) {
			int table_x, table_y;
			string item;
			cin >> table_x >> table_y >> item; cin.ignore();
			cerr << table_x << ' ' << table_y << ' ' << item << endl;
			for(auto &table: tables) {
				if(table->loc != Vec(table_x, table_y)) continue;
				table->items = str2Items(item);
				// table->print();
			}
		}

		string oven_contents; // ignore until wood 1 league
		int oven_timer;
		cin >> oven_contents >> oven_timer; cin.ignore();
		cerr << "oven: " << oven_contents << ' ' << oven_timer << endl;
		oven->items = str2Items(oven_contents);
		oven->timer = oven_timer;
		// oven->print();

		vector<Items> orders;

		cerr << "orders: " << endl;
		int num_customers; // the number of customers currently waiting for food
		cin >> num_customers; cin.ignore();
		for (int i = 0; i < num_customers; i++) {
			string customer_item;
			int customer_award;
			cin >> customer_item >> customer_award; cin.ignore();
			cerr << customer_item << ' ' << customer_award << endl;
			orders.emplace_back(str2Items(customer_item));
			// orders.back().print();
		}

		if(player.items.contains(EFood::DISH)) dishCnt--;
		if(partner.items.contains(EFood::DISH)) dishCnt--;
		for(auto &container: kitchen.containers) {
			if(container->items.contains(EFood::DISH)) dishCnt--;
		}
		dishWasher->items = dishCnt ? Items(EFood::DISH) : Items();
		// cerr << "dishCnt " << dishCnt << endl;

		shared_ptr<Container> nearestEmptyTable;
		for(auto &table: tables) {
			if(!table->items.empty()) continue;
			// table->print();
			if(!nearestEmptyTable
				|| player.loc.distance(table->loc) < player.loc.distance(nearestEmptyTable->loc)) {
				nearestEmptyTable = table;
				// cerr << "is near ↑" << endl;
			}
		}
		cerr << "nearest empty table:" << endl;
		nearestEmptyTable->print();

		vector<shared_ptr<Container>> containersNonEmpty;
		vector<shared_ptr<Container>> containersWithDish;
		vector<shared_ptr<Container>> containersWithoutDish;
		// cerr << "find container with items: " << endl;
		for(auto &container: kitchen.containers) {
			if(container->items.empty()) continue;
			containersNonEmpty.emplace_back(container);
			if(container->items.contains(EFood::DISH)) {
				// cerr << "container is with dish ↓" << endl;
				containersWithDish.emplace_back(container);
			}
			else {
				// cerr << "container is without dish ↓" << endl;
				containersWithoutDish.emplace_back(container);
			}
			container->print();
		}

		Items finish;
		for(auto &container: containersWithoutDish) {
			finish = finish | container->items;
		}

		function<function<void()>(Items)> send, take, produce, make, merge, combine;
		function<function<void()>()> clearHand;
		function<shared_ptr<Container>(Items)> containerWith;

		send = [&](const Items &target) {
			cerr << "send: "; target.print();
			if(player.items == target) return Chef::use(window->loc);
			if(auto &&res = combine(target)) {
				return res;
			}
			return function<void()>();
		};

		take = [&](const Items &target) {
			cerr << "take: "; target.print();
			if(auto &&container = containerWith(target); container != nullptr) {
				return Chef::use(container->loc);
			}
			return function<void()>();
		};
		
		produce = [&](const Items &target) {  // require no container has
			cerr << "produce: "; target.print();
			if(auto &&res = make(target)) { 
				return res;
			}
			if(auto &&res = merge(target)) {
				return res;
			}
			cerr << "can not produce by any method" << endl;
			return function<void()>();
		};

		make = [&](const Items &target) {
			cerr << "make: "; target.print();
			if(auto &&found = kitchen.makers.find(target); found != kitchen.makers.end()) {
				cerr << "find maker" << endl;
				auto &maker = found->second;
				if(!maker->isMaking()) {
					cerr << "maker is not making" << endl;
					if(player.items == maker->recipes[found->first]) {
						cerr << "player can use maker" << endl;
						return Chef::use(maker->loc);
					}
					cerr << "can not use maker" << endl;
					if(auto &&res = take(maker->recipes[found->first])) {
						if(!player.items.empty()) {
							return clearHand();
						}
						return res;
					}
					cerr << "can not take material" << endl;
					if(auto &&res = produce(maker->recipes[found->first])) {
						return res;
					}
					cerr << "can not produce material" << endl;
				}
				cerr << "maker is making" << endl;
			}
			return function<void()>();
		};

		merge = [&](const Items &target) {
			cerr << "merge: "; target.print();
			if(auto &&found = kitchen.mergeRecipes.find(Items(target)); found != kitchen.mergeRecipes.end()) {
				cerr << "find recipe" << endl;
				auto &[product, materials] = *found;
				if(player.items == materials.first) {
					cerr << "player is holding first material" << endl;
					if(auto &&res = take(materials.second)) {
						return res;
					}
					cerr << "player can not take second material" << endl;
					if(auto &&res = produce(materials.second)) {
						return res;
					}
					cerr << "can not produce second material" << endl;
				}
				if(player.items == materials.second) {
					cerr << "player is holding second material" << endl;
					if(auto &&res = take(materials.first)) {
						return res;
					}
					cerr << "player can not take first material" << endl;
					if(auto &&res = produce(materials.first)) {
						return res;
					}
					cerr << "can not produce first material" << endl;
				}
				cerr << "player does has material" << endl;
				if(auto &&res = take(materials.first)) {
					if(!player.items.empty()) {
						return clearHand();
					}
					return res;
				}
				cerr << "player can not take first material" << endl;
				if(auto &&res = produce(materials.first)) {
					return res;
				}
				cerr << "can not produce first material" << endl;
			}
			return function<void()>();
		};

		combine = [&](const Items &target) {
			cerr << "combine: "; target.print();

            if(!oven->items.empty()
                && (!oven->isMaking() || oven->timer <= 2)) {
                cerr << "oven is done" << endl;
                if(!player.items.empty()) {
                    return clearHand();
                }
                cerr << "go to use oven" << endl;
                return Chef::use(oven->loc);
            }

			// according target to set unfinish
			Items unfinish = (finish & target) ^ target;
			unfinish.remove(EFood::DISH);

			shared_ptr<Container> rightContainerWithDish;
			shared_ptr<Container> nearestContainerWithDish;
			for(auto &container: containersWithDish) {
				if(!nearestContainerWithDish
					|| player.loc.distance(container->loc) < player.loc.distance(nearestContainerWithDish->loc)) {
					nearestContainerWithDish = container;
				}
				if(!container->items.isMaterialOf(target)) continue;
				if(!rightContainerWithDish
					|| (unfinish & container->items).count() > (unfinish & rightContainerWithDish->items).count()
					|| ((unfinish & container->items).count() == (unfinish & rightContainerWithDish->items).count()
						&& (finish & container->items).count() > (finish & rightContainerWithDish->items).count())) {
					rightContainerWithDish = container;
				}
			}

			Items need = unfinish;

			cerr << "check if player taking dish" << endl;
			if(player.items.contains(EFood::DISH)) {
				if(!player.items.isMaterialOf(target)) {
					cerr << "take wrong dish" << endl;
					if(rightContainerWithDish) {
						cerr << "change with other dish" << endl;
						return clearHand();
					}
					cerr << "wash dish" << endl;
					return Chef::use(dishWasher->loc);
				}
				cerr << "take right dish" << endl;
				need = (need & player.items) ^ need;
			}
			else {
				if(rightContainerWithDish) {
					need = (need & rightContainerWithDish->items) ^ need;
				}
				else {
					need = (need & player.items) ^ need;
				}
			}

			cerr << "need: "; need.print();

			if(!need.empty()) {
				if(!player.items.empty() && player.items.isMaterialOf(target)) {
					cerr << "player is hold need of target" << endl;
					if(!player.items.contains(EFood::DISH)) {
						cerr << "player is without dish" << endl;
						if(rightContainerWithDish) {
							if((player.items & rightContainerWithDish->items).empty()) {
								cerr << "append to rgiht with dish, clear" << endl;
								return Chef::use(rightContainerWithDish->loc);
							}
						}
						cerr << "player has repeat food, clear" << endl;
						return clearHand();
					}
					for(int i = 0; i < 32; i++) {
						auto &&food = static_cast<EFood>(i);
						Items foodToItems(food);
						if(!target.contains(food) || player.items.contains(food)) continue;
						if(auto &&res = take(foodToItems)) {
							return res;
						}
					}
				}
				if(player.items.contains(EFood::DISH)) {
					cerr << "player is holding dish, can not do any thing." << endl;
					return clearHand();
				}
				cerr << "find what need to make" << endl;
				for(int i = 0; i < 32; i++) {
					auto &&food = static_cast<EFood>(i);
					Items foodToItems(food);
					if(!need.contains(food)) continue;
					if(player.items == foodToItems) {
						return Chef::use(rightContainerWithDish->loc);
						// return clearHand();
					}
					cerr << "find food to produce" << endl;
					if(auto &&res = produce(foodToItems)) {
						return res;
					}
				}
				cerr << "nothing can do?" << endl;
				return function<void()>();
			}
			
			cerr << "everything is done. start combine" << endl;
			if(!player.items.isMaterialOf(target)) {
				cerr << "player is holding wrong items, clear hand" << endl;
				return clearHand();
			}

			if(!player.items.contains(EFood::DISH)) {
				cerr << "go to take dish" << endl;
				if(rightContainerWithDish) {
					return Chef::use(rightContainerWithDish->loc);
				}
				if(nearestContainerWithDish) {
					return Chef::use(nearestContainerWithDish->loc);
				}
				cerr << "no dish can take" << endl;
				return function<void()>();
			}

			cerr << "take every thing can take" << endl;
			for(int i = 0; i < 32; i++) {
				auto &&food = static_cast<EFood>(i);
				Items foodToItems(food);
				if(!target.contains(food) || player.items.contains(food)) continue;
				if(auto &&res = take(Items(food))) {
					return res;
				}
			}
			return function<void()>();
		};

		clearHand = [&]() {
			cerr << "clear hand" << endl;
			return Chef::use(nearestEmptyTable->loc);
		};

		containerWith = [&](const Items &target) {
			cerr << "container with: "; target.print();
			shared_ptr<Container> nearest;
			for(auto &container: kitchen.containers) {
				if(container->items != target) continue;
				if(!nearest
					|| player.loc.distance(container->loc) < player.loc.distance(nearest->loc)) {
					nearest = container;
				}
			}
			return nearest;
		};
		
		function<void()> nextStep;
		for(int i = 0; i < num_customers; i++) {
			if(auto &&res = send(orders[i])) {
				nextStep = res;
				break;
			}
		}
		if(!nextStep) nextStep = Chef::wait();
		nextStep();
	}
}