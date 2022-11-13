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
	shared_ptr<ChoppingBoard> choppingBoard = make_shared<ChoppingBoard>();
	shared_ptr<Oven> oven = make_shared<Oven>();
	choppingBoard->recipes = {
		{Items(EFood::CHOPPED_DOUGH), Items(EFood::DOUGH)},
		{Items(EFood::CHOPPED_STRAWBERRIES), Items(EFood::STRAWBERRIES)},
	};
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
			case 'C': choppingBoard->loc = loc; break;
			case 'O': oven->loc = loc; break;
			}
		}
	}
	
	cerr << "default tables: " << endl;
	for(auto &table: tables) { table->print(); }

	Kitchen kitchen;
	kitchen.window = window;
	kitchen.dishWasher = dishWasher;
	kitchen.containers.insert(kitchen.containers.end(), tables.begin(), tables.end());
	kitchen.containers.emplace_back(dishWasher);
	kitchen.containers.emplace_back(blueberryCrate);
	kitchen.containers.emplace_back(iceCreamCrate);
	kitchen.containers.emplace_back(strawberriesCrate);
	
	for(auto &maker: makers) {
		for(auto &recipe: maker->recipes) {
			kitchen.makers.emplace(recipe.first, maker);
		}
	}

	// game loop
	while (1) {
		int dishCnt = 3;

		int turns_remaining;
		cin >> turns_remaining; cin.ignore();
		cerr << "turns remaining " << turns_remaining << endl;

		if(turns_remaining < 0) break;

		int player_x;
		int player_y;
		string player_item;
		cin >> player_x >> player_y >> player_item; cin.ignore();
		cerr << "player " << player_x << ' ' << player_y << endl << "player items: " << player_item << endl;

		Chef player;
		player.loc = Vec(player_x, player_y);
		player.items = str2items(player_item);
		player.items.print();

		int partner_x;
		int partner_y;
		string partner_item;
		cin >> partner_x >> partner_y >> partner_item; cin.ignore();
		cerr << "partner " << partner_x << ' ' << partner_y << endl << "partner items: " << player_item << endl;

		Chef partner;
		player.loc = Vec(partner_x, partner_y);
		partner.items = str2items(partner_item);
		partner.items.print();

		cerr << "update tables " << endl;
		int num_tables_with_items; // the number of tables in the kitchen that currently hold an item
		cin >> num_tables_with_items; cin.ignore();
		for(auto &table: tables) table->items.clear();
		for (int i = 0; i < num_tables_with_items; i++) {
			int table_x;
			int table_y;
			string item;
			cin >> table_x >> table_y >> item; cin.ignore();
			cerr << table_x << ' ' << table_y << ' ' << item << endl;
			for(auto &table: tables) {
				if(table->loc != Vec(table_x, table_y)) continue;
				table->items = str2items(item);
				table->print();
				if(table->items.contains(EFood::DISH)) dishCnt--;
			}
		}

		string oven_contents; // ignore until wood 1 league
		int oven_timer;
		cin >> oven_contents >> oven_timer; cin.ignore();

		vector<Items> orders;

		int num_customers; // the number of customers currently waiting for food
		cin >> num_customers; cin.ignore();
		for (int i = 0; i < num_customers; i++) {
			string customer_item;
			int customer_award;
			cin >> customer_item >> customer_award; cin.ignore();
			orders.emplace_back(str2items(customer_item));
		}

		cerr << "orders: " << endl;
		for(auto &order: orders) {
			order.print();
		}

		if(player.items.contains(EFood::DISH)) dishCnt--;
		if(partner.items.contains(EFood::DISH)) dishCnt--;

		dishWasher->items = dishCnt ? Items(EFood::DISH) : Items();

		cerr << "dishCnt " << dishCnt << endl;

		shared_ptr<Container> nearestEmptyTable;
		for(auto &table: tables) {
			if(!table->items.empty()) continue;
			if(!nearestEmptyTable
				|| player.loc.distance(table->loc) < player.loc.distance(nearestEmptyTable->loc)) {
				nearestEmptyTable = table;
			}
		}

		function<function<void()>(Items)> nextStep = [&](const Items &target) {
			cerr << "target: ";
			target.print();

			// init
			Items finish, unfinish;
			vector<shared_ptr<Container>> containersWithDish;
			vector<shared_ptr<Container>> containersWithoutDish;
			cerr << "find container with items: " << endl;
			for(auto &container: kitchen.containers) {
				if(container->items.empty()) continue;
				container->print();
				if(container->items == target) {
					cerr << "container contains target, use it." << endl;
					return Chef::use(container->loc);
				}
				if(container->items.contains(EFood::DISH)) {
					cerr << "container is with dish ↑." << endl;
					containersWithDish.emplace_back(container);
				}
				else {
					cerr << "container is without dish ↑." << endl;
					containersWithoutDish.emplace_back(container);
					finish = finish | container->items;
				}
			}
			finish = finish & target;
			unfinish = finish ^ target;
			
			cerr << "finish: ";
			finish.print();
			cerr << "unfinish: ";
			unfinish.print();

			cerr << "check cururent state" << endl;
			// making state ↓
			if(!target.contains(EFood::DISH)) {
				cerr << "target contains DISH (making state)" << endl;
				// can combine to target
				if(player.items.isMaterialOf(target)) {
					shared_ptr<Container> nearestCanCombine;
					for(int i = 0; i < 32; i++) {
						auto &&food = static_cast<EFood>(i);
						Items foodToItems(food);
						if(!target.contains(food) || player.items.contains(food)) continue;
						cerr << "tmp unfinish food : ";
						foodToItems.print();
						for(auto &container: kitchen.containers) {
							if(container->items == foodToItems) {
								cerr << "find a container that contain: " << endl;
								container->print();
								if(!nearestCanCombine
									|| player.loc.distance(container->loc) < player.loc.distance(nearestCanCombine->loc)) {
									nearestCanCombine = container;
								}
							}
						}
					}
					if(!nearestCanCombine) {
						cerr << "nothing can combine, clear" << endl;
						return Chef::use(nearestEmptyTable->loc);
					}
					return Chef::use(nearestCanCombine->loc);
				}
				cerr << "check any maker can make target" << endl;
				// check any maker can make target
				if(auto &&found = kitchen.makers.find(target); found != kitchen.makers.end()) {
					auto &maker = found->second;
					cerr << "find maker: " << endl;
					cerr << maker->loc.x << ' ' << maker->loc.y << endl;
					if(player.items == maker->recipes[target]) {
						cerr << "can use it" << endl;
						return Chef::use(maker->loc);
					}
					cerr << "can not use, try make material" << endl;
					return nextStep(maker->recipes[target]);
				}
				if(!nearestEmptyTable) {
					cerr << "no empty table" << endl;
					return Chef::wait();
				}
				cerr << "clear hand use: ";
				nearestEmptyTable->loc;
				return Chef::use(nearestEmptyTable->loc);
			}
			
			cerr << "combine state" << endl;
			// combine state ↓
			if(player.items == target) {  // player has target
				cerr << "player has target" << endl;
				return Chef::use(window->loc);
			}

			shared_ptr<Container> rightContainerWithDish;
			shared_ptr<Container> nearestContainerWithDish;
			for(auto &container: containersWithDish) {
				if(!nearestContainerWithDish
					|| player.loc.distance(container->loc) < player.loc.distance(nearestContainerWithDish->loc)) {
					nearestContainerWithDish = container;
				}
				if(!container->items.isMaterialOf(target)) continue;
				if(!rightContainerWithDish
					|| (unfinish & container->items).count() > (unfinish & rightContainerWithDish->items).count()) {
					rightContainerWithDish = container;
				}
			}
			if(rightContainerWithDish) {
				cerr << "find rightContainerWithDish: ";
				rightContainerWithDish->print();
			}
			if(nearestContainerWithDish) {
				cerr << "find nearestContainerWithDish: ";
				nearestContainerWithDish->print();
			}
			// player has no items (check require state)
			if(player.items.empty()) {
				cerr << "player has no items" << endl;
				cerr << "find container with dish: " << endl;
				for(auto &container: containersWithDish) {
					if(container->items == target) {
						cerr << "find a container == target" << endl;
						return Chef::use(container->loc);
					}
				}
				if(!rightContainerWithDish) {
					if(!nearestContainerWithDish) {
						cerr << "no right container with dish && no nearest with dish 'wait'" << endl;
						return Chef::wait();
					}
					cerr << "use nearest: " << endl;
					nearestContainerWithDish->print();
					return Chef::use(nearestContainerWithDish->loc);
				}
				cerr << "use right container with dish: " << endl;
				rightContainerWithDish->print();
				return Chef::use(rightContainerWithDish->loc);
			}
			
			// player holding with dish
			if(player.items.contains(EFood::DISH)){
				cerr << "player hold with dish" << endl;
				// player has wrong dish, clear hand
				if(!player.items.isMaterialOf(target)) {
					cerr << "player has wrong dish, clear hand";
					if(rightContainerWithDish) {
						cerr << "ther is right container with dish, clear hand" << endl;
						Chef::use(nearestEmptyTable->loc);
					}
					cerr << "clear hand by using dishwasher" << endl;
					return Chef::use(kitchen.dishWasher->loc);
				}
				cerr << "player has right dish" << endl;
				cerr << "search near can combine" << endl;
				shared_ptr<Container> nearestContainerCanCombine;
				for(auto &container: containersWithoutDish) {
					if((!container->items.isMaterialOf(player.items))
						&& container->items.isMaterialOf(target)) {
						if(!nearestContainerCanCombine
							|| player.loc.distance(container->loc) < player.loc.distance(nearestContainerCanCombine->loc)) {
							nearestContainerCanCombine = container;
						}
					}
				}
				if(!nearestContainerCanCombine) {
					cerr << " nothing can combine, clear hand" << endl;
					// nothing can combine
					return Chef::use(nearestEmptyTable->loc);
				}
				cerr << "combine with target:" << endl;
				nearestContainerCanCombine->print();
				return Chef::use(nearestContainerCanCombine->loc);
			}
			cerr << "player is holding but without dish" << endl;
			// else player is holding but without dish
			for(int i = 0; i < 32; i++) {
				auto &&food = static_cast<EFood>(i);
				if(!unfinish.contains(food)) continue;
				Items foodToItems(food);
				return nextStep(foodToItems);
			}
			cerr << "can not make target" << endl;
			return Chef::use(nearestEmptyTable->loc);
		};
		cerr << "function start run " << endl;
		nextStep(orders[0])();
	}
}