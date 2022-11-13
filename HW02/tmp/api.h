#include <iostream>
#include <utility>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <string_view>

class Items {
public:
	constexpr Items(): contents_() { }
	constexpr Items(int val): contents_(val) {}
	constexpr Items(unsigned long long val): contents_(val) {}
	Items(const std::string &str) {
		std::string_view sv(str);
		for(size_t i = 0, end = sv.npos; i < sv.size(); i = end) {
			end = sv.find('-', i);
			if(end == sv.npos) end = sv.size();
			if(const auto &&found = getFoodMapper().find(sv.substr(i, end-i)); found != getFoodMapper().end()) {
				add(found->second);
			}
		}
	}
	constexpr Items(const Items &rhs) { add(rhs); }
	constexpr Items(Items &&rhs) { *this = std::move(rhs); }
	Items &operator=(const Items &rhs) {
		contents_ = rhs.contents_;
		return *this;
	}
	Items &operator=(Items &&rhs) {
		if(this == &rhs) return *this;
		contents_ = std::move(rhs.contents_);
		return *this;
	}
	Items operator&(const Items &rhs) const { return Items(val() & rhs.val()); }
	Items operator|(const Items &rhs) const { return Items(val() | rhs.val()); }
	Items operator^(const Items &rhs) const { return Items(val() ^ rhs.val()); }
	Items &operator&=(const Items &rhs) { return *this = *this & rhs; }
	Items &operator|=(const Items &rhs) { return *this = *this | rhs; }
	Items &operator^=(const Items &rhs) { return *this = *this ^ rhs; }
	bool operator==(const Items &rhs) const { return contents_ == rhs.contents_; }
	bool operator!=(const Items &rhs) const { return contents_ != rhs.contents_; }
	void add(const Items &rhs) { contents_ |= rhs.contents_; }
	template <typename T, typename... Args>
	void add(const T &head, const Args &...tails) { add(head); add(tails...); }
	void remove(const Items &rhs) { contents_ ^= contents_ & rhs.contents_; }
	template <typename T, typename... Args>
	void remove(const T &head, const Args &...tails) { remove(head); remove(tails...); }
	void clear(){ contents_.reset(); }
	bool contains(const Items &rhs) const { return (rhs.contents_ & contents_) == rhs.contents_; }
	bool empty() const { return contents_.none(); }
	int count() const { return contents_.count(); }
	unsigned long long val() const { return contents_.to_ullong(); }
	static const Items DISH, BLUEBERRIES, ICE_CREAM, CHOPPED_STRAWBERRIES, CROISSANT, TART, STRAWBERRIES, DOUGH, CHOPPED_DOUGH, RAW_TART;
private:
	static constexpr size_t size_ = 64;
	std::bitset<size_> contents_;
	enum class EFood: unsigned long long { 
		DISH = 0,
		BLUEBERRIES,
		ICE_CREAM,
		CHOPPED_STRAWBERRIES,
		CROISSANT,
		TART,
		STRAWBERRIES,
		DOUGH,
		CHOPPED_DOUGH,
		RAW_TART,
	};
	static const std::array<std::string_view, size_> &getFoodNames() {
		using namespace std::literals;
		static constexpr std::array<std::string_view, size_> FOOD_NAMES = {
			"DISH"sv,
			"BLUEBERRIES"sv,
			"ICE_CREAM"sv,
			"CHOPPED_STRAWBERRIES"sv,
			"CROISSANT"sv,
			"TART"sv,
			"STRAWBERRIES"sv,
			"DOUGH"sv,
			"CHOPPED_DOUGH"sv,
			"RAW_TART"sv,
		};
		return FOOD_NAMES;
	}
	static const std::unordered_map<std::string_view, EFood> &getFoodMapper() {
		using namespace std::literals;
		static const std::unordered_map<std::string_view, EFood> FOOD_MAPPER = {
			{ "DISH"sv, EFood::DISH },
			{ "BLUEBERRIES"sv, EFood::BLUEBERRIES },
			{ "ICE_CREAM"sv, EFood::ICE_CREAM },
			{ "CHOPPED_STRAWBERRIES"sv, EFood::CHOPPED_STRAWBERRIES },
			{ "CROISSANT"sv, EFood::CROISSANT },
			{ "TART"sv, EFood::TART },
			{ "STRAWBERRIES"sv, EFood::STRAWBERRIES },
			{ "DOUGH"sv, EFood::DOUGH },
			{ "CHOPPED_DOUGH"sv, EFood::CHOPPED_DOUGH },
			{ "RAW_TART"sv, EFood::RAW_TART },
		};
		return FOOD_MAPPER;
	}
	void add(const EFood &food) { contents_[static_cast<unsigned long long>(food)] = 1; }
	void remove(const EFood &food) { contents_[static_cast<unsigned long long>(food)] = 0; }
	constexpr Items(const EFood &food): contents_(1 << static_cast<unsigned long long>(food)) {}
};
const Items Items::DISH = Items(Items::EFood::DISH);
const Items Items::BLUEBERRIES = Items(Items::EFood::BLUEBERRIES);
const Items Items::CHOPPED_STRAWBERRIES = Items(Items::EFood::CHOPPED_STRAWBERRIES);
const Items Items::CROISSANT = Items(Items::EFood::CROISSANT);
const Items Items::TART = Items(Items::EFood::TART);
const Items Items::STRAWBERRIES = Items(Items::EFood::STRAWBERRIES);
const Items Items::DOUGH = Items(Items::EFood::DOUGH);
const Items Items::CHOPPED_DOUGH = Items(Items::EFood::CHOPPED_DOUGH);
const Items Items::RAW_TART = Items(Items::EFood::RAW_TART);

template<>
struct std::hash<Items> {
	std::size_t operator()(const Items& k) const noexcept {
		return k.val();
	}
};

template <typename T, typename U>
struct std::hash<std::pair<T, U>> {
	std::size_t operator()(const std::pair<T, U> &x) const {
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

class Vector2D {
public:
	int x, y;
	Vector2D(): x(0), y(0) {};
	Vector2D(int x, int y): x(x), y(y) {};
	Vector2D(std::pair<int, int> xy): x(xy.first), y(xy.second) {};
	bool operator==(const Vector2D &rhs) const { return (x == rhs.x && y == rhs.y); }
	bool operator!=(const Vector2D &rhs) const { return (x != rhs.x || y != rhs.y); }
	bool operator<(const Vector2D &rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
	Vector2D operator+(const Vector2D &rhs) const { return Vector2D(x+rhs.x, y+rhs.y); }
	Vector2D operator-(const Vector2D &rhs) const { return Vector2D(x-rhs.x, y-rhs.y); }
	Vector2D &operator+=(const Vector2D &rhs) { return *this = *this + rhs; }
	Vector2D &operator-=(const Vector2D &rhs) { return *this = *this - rhs; }
private:
};

/*
class ILocation {
public:
	Vector2D location;
};

class IContainer{
public:
	Items items;
};

class IInteractable {
public:
	virtual bool isInteractable(const Items &holding) const = 0;
	virtual void interact(Items &holding) = 0;
};

class IProducer {
public:
	std::unordered_set<Items> products;
};

class Takable: virtual public IContainer {
public:
	bool canTake(const Items &holding) const {
		return holding.empty() && !items.empty();
	};
	Items takeResult([[maybe_unused]] const Items &holding) const {
		return items;
	}
	virtual void take(Items &holding) = 0;
};

class Placeable: virtual public IContainer {
public:
	bool canPlace(const Items &holding) const {
		return !holding.empty() && items.empty();
	}
	Items placeResult([[maybe_unused]] const Items &holding) const {
		return Items();
	}
	virtual void place(Items &holding) = 0;
};

class Mergeable: virtual public IContainer {
public:
	const std::unordered_map<std::pair<Items, Items>, Items> mergeTable = {
		{ std::make_pair(Items(EFood::BLUEBERRIES), Items(EFood::DOUGH)), Items(EFood::RAW_TART) },
		{ std::make_pair(Items(EFood::DOUGH), Items(EFood::BLUEBERRIES)), Items(EFood::RAW_TART) },
	};
	bool canMerge(const Items &holding) const {
		return mergeTable.count(std::make_pair(holding, items));
	};
	Items mergeResult(Items &holding) const {
		return mergeTable.at(std::make_pair(holding, items));
	}
	virtual void merge(Items &holding) = 0;
};

class Choppable {
public:
	const std::unordered_map<Items, Items> chopTable = {
		{ Items(EFood::STRAWBERRIES), Items(EFood::CHOPPED_STRAWBERRIES) },
		{ Items(EFood::DOUGH), Items(EFood::CHOPPED_DOUGH) },
	};
	bool canChop(const Items &holding) const {
		return chopTable.count(holding);
	};
	Items chopResult(const Items &holding) const {
		return chopTable.at(holding);
	}
	virtual void chop(Items &holding) = 0;
};

class Bakeable: virtual public IContainer {
public:
	const std::unordered_map<Items, Items> bakeTable = {
		{ Items(EFood::DOUGH), Items(EFood::CROISSANT) },
		{ Items(EFood::RAW_TART), Items(EFood::TART) },
	};
	bool isBaking([[maybe_unused]] Items &holding) const {
		return !items.empty() && bakeTable.count(items);
	}
	bool canBake(const Items &holding) {
		return bakeTable.count(holding);
	};
	Items bakeResult(const Items &holding) const {
		return bakeTable.at(holding);
	}
	virtual void bake(Items &holding) = 0;
	int timer;
};

class Combinable: virtual public IContainer {
public:
	std::unordered_set<Items> combinableFood = {
		Items(EFood::BLUEBERRIES),
		Items(EFood::ICE_CREAM),
		Items(EFood::CHOPPED_STRAWBERRIES),
		Items(EFood::CROISSANT),
		Items(EFood::TART),
	};
	bool canCombine(const Items &holding) const {
		if(holding.empty() || items.empty()) {
			return false;
		}
		return (holding.contains(EFood::DISH) ^ items.contains(EFood::DISH)) // only one dish can exist
				&& (combinableFood.count(holding) || combinableFood.count(items))  // food can be merge
				&& (holding & items).empty();  // no repeat food
	};
	Items combineResult(const Items &holding) const {
		return holding | items;
	}
	virtual void combine(Items &holding) = 0;
};

class Washable: virtual public IContainer {
public:
	bool canWash(const Items &holding) const {
		return Items(EFood::DISH).isMaterialOf(holding);
	};
	Items washResult([[maybe_unused]] const Items &holding) const {
		return Items(EFood::DISH);
	}
	virtual void wash(Items &holding) = 0;
};

class Sendable: virtual public IContainer {
public:
	bool canSend(const Items &holding) const {
		return std::any_of(orders.begin(), orders.end(), [&holding](const auto &val){
			return holding == val.first;
		});
		// for(auto &[items, award]: orders) {
		// 	if(holding == items)
		// }
	};
	int sendResult(const Items &holding) const {
		int res = 0;
		for(auto &[items, award]: orders) {
			if(holding == items && award > res) {
				res = award;
			}
		}
		return res;
	}
	virtual void send(Items &holding) = 0;
	std::vector<std::pair<Items, int>> orders;
};

class Table: public ILocation, public IInteractable, public Takable, public Placeable, public Mergeable, public Combinable {
	virtual void take(Items &holding) override {
		holding = takeResult(holding);
		items.clear();
	}
	virtual void place(Items &holding) override {
		holding.clear();
		items = placeResult(holding);
	}
	virtual void merge(Items &holding) override {
		holding = mergeResult(holding);
		items.clear();
	}
	virtual void combine(Items &holding) override {
		if(holding.contains(EFood::DISH)) {
			holding = combineResult(holding);
			items.clear();
		}
		else {
			items = combineResult(holding);
			holding.clear();

		}
	}	
	virtual bool isInteractable(const Items &holding) const override {
		return canTake(holding) || canPlace(holding) || canMerge(holding) || canCombine(holding);
	}
	virtual void interact(Items &holding) override {
		if(canTake(holding)) {
			return take(holding);
		}
		if(canPlace(holding)) {
			return place(holding);
		}
		if(canMerge(holding)) {
			return merge(holding);
		}
	}
};

class DishWasher: public ILocation, public IInteractable, public Takable, public Combinable, public Washable {
	virtual void take(Items &holding) override {
		holding = takeResult(holding);
		--dishCount;
		if(dishCount == 0) {
			items.clear();
		}
	}
	virtual void combine(Items &holding) override {
		holding = combineResult(holding);
		--dishCount;
		if(dishCount == 0) {
			items.clear();
		}
	}
	virtual void wash(Items &holding) {
		holding = washResult(holding);
	}
	virtual bool isInteractable(const Items &holding) const override {
		return canTake(holding) | canCombine(holding) | canWash(holding);
	}
	virtual void interact(Items &holding) override {
		if(canTake(holding)) {
			return take(holding);
		}
		if(canCombine(holding)) {
			return combine(holding);
		}
		if(canWash(holding)) {
			return wash(holding);
		}
	}
	int dishCount;
};


class Window: public ILocation, public IInteractable, public Sendable {
	virtual void send(Items &holding) override {
		holding.clear();
	}
	virtual bool isInteractable(const Items &holding) const override {
		return canSend(holding);
	}
	virtual void interact(Items &holding) override {
		if(canSend(holding)) {
			return send(holding);
		}
	}
	std::vector<std::pair<Items, int>> orders;
};

class Crate: public ILocation, public IInteractable, public Takable, public Mergeable, public Combinable {
	virtual void take(Items &holding) override {
		holding = items;
	}
	virtual void merge(Items &holding) override {
		holding = items;
	}
	virtual void combine(Items &holding) override {
		holding = combineResult(holding);
	}
	virtual bool isInteractable(const Items &holding) const override {
		return canTake(holding);
	}
	virtual void interact(Items &holding) override {
		if(canTake(holding)) {
			return take(holding);
		}
		if(canMerge(holding)) {
			return merge(holding);
		}
		if(canCombine(holding)) {
			return combine(holding);
		}
	}	
};

class ChoppingBoard: public ILocation, public IInteractable, public Choppable {
	virtual void chop(Items &holding) override {
		holding = chopResult(holding);
	}
	virtual bool isInteractable(const Items &holding) const override {
		return canChop(holding);
	}
	virtual void interact(Items &holding) override {
		if(canChop(holding)) {
			return chop(holding);
		}
	}
};

class Oven: public ILocation, public IInteractable, public Takable, public Bakeable, public Combinable {
	virtual void take(Items &holding) override {
		holding = takeResult(holding);
		items.clear();
	}
	virtual void bake(Items &holding) override {
		items = holding;
		holding.clear();
		timer = 10;
	}
	virtual void combine(Items &holding) {
		holding = combineResult(holding);
		items.clear();
	}
	virtual bool isInteractable(const Items &holding) const override {
		return canTake(holding);
	}
	virtual void interact(Items &holding) override {
		if(canTake(holding)) {
			return take(holding);
		}
		if(canBake(holding)) {
			return bake(holding);
		}
		if(canCombine(holding)) {
			return combine(holding);
		}
	}
};


class Kitchen{
public:
	Kitchen(const std::vector<std::string> &kitchen_lines) {
		dishWasher = std::make_shared<DishWasher>();
		window = std::make_shared<Window>();
		blueberriesCrate = std::make_shared<Crate>();
		iceCreamCrate = std::make_shared<Crate>();
		strawberriesCrate = std::make_shared<Crate>();
		doughCrate = std::make_shared<Crate>();
		choppingBoard = std::make_shared<ChoppingBoard>();
		oven = std::make_shared<Oven>();
		for(size_t i = 0; i < 7; i++) {
			for(size_t j = 0; j < 11; j++) {
				auto &&location = Vector2D(j, i);
				std::shared_ptr<Table> table;
				switch(kitchen_lines[i][j]) {
					case '.': {
						break;
					}
					case '#': {
						table = std::make_shared<Table>();
						table->location = location;
						tables.emplace_back(table);
						break;
					}
					case 'D': {
						dishWasher->location = location;
						break;
					}
					case 'W': {
						window->location = location;
						break;
					}
					case 'B': {
						blueberriesCrate->location = location;
						break;
					}
					case 'I': {
						iceCreamCrate->location = location;
						break;
					}
					case 'S': {
						strawberriesCrate->location = location;
						break;
					}
					case 'H': {
						doughCrate->location = location;
						break;
					}
					case 'C': {
						choppingBoard->location = location;
						break;
					}
					case 'O': {
						oven->location = location;
						break;
					}
				}
			}
		}


		interactableObjs.insert(interactableObjs.end(), tables.begin(), tables.end());
		interactableObjs.emplace_back(dishWasher);
		interactableObjs.emplace_back(window);
		interactableObjs.emplace_back(blueberriesCrate);
		interactableObjs.emplace_back(iceCreamCrate);
		interactableObjs.emplace_back(strawberriesCrate);
		interactableObjs.emplace_back(doughCrate);
		interactableObjs.emplace_back(choppingBoard);
		interactableObjs.emplace_back(oven);
	}
	std::vector<std::shared_ptr<IInteractable>> interactableObjs;
	std::vector<std::shared_ptr<Table>> tables;
	std::shared_ptr<Crate> blueberriesCrate;
	std::shared_ptr<Crate> iceCreamCrate;
	std::shared_ptr<Crate> strawberriesCrate;
	std::shared_ptr<Crate> doughCrate;
	std::shared_ptr<Window> window;
	std::shared_ptr<DishWasher> dishWasher;
	std::shared_ptr<ChoppingBoard> choppingBoard;
	std::shared_ptr<Oven> oven;
};
*/

class Action {
	enum class EType {
		MOVE,
		USE,
		WAIT,
	};
	// II1
};