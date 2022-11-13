#include <bits/stdc++.h>
#include <functional>
#include "vec.h"

using namespace std;

enum class EFood { UNDEFINED, DISH, BLUEBERRIES, ICE_CREAM, STRAWBERRIES, CHOPPED_STRAWBERRIES, DOUGH, CHOPPED_DOUGH, CROISSANT, RAW_TART, TART };
string EFood2Str[32] = {"UNDEFINED", "DISH", "BLUEBERRIES", "ICE_CREAM", "STRAWBERRIES", "CHOPPED_STRAWBERRIES", "DOUGH", "CHOPPED_DOUGH", "CROISSANT", "RAW_TART", "TART" };

class Items {
public:
	Items(): contents() { }
	Items(unsigned long val): contents(val) {}
	Items(const Items &rhs) { *this = rhs; }
	template <typename... Args>
	Items(Args... args): contents() { add(args...); }
	Items &operator=(const Items &rhs) {
		contents = rhs.contents;
		return *this;
	}
	Items &operator=(Items &&rhs) {
		if(this == &rhs) return *this;
		contents = std::move(rhs.contents);
		return *this;
	}
	Items operator&(const Items &rhs) const { return Items(toUL() & rhs.toUL()); }
	Items operator|(const Items &rhs) const { return Items(toUL() | rhs.toUL()); }
	Items operator^(const Items &rhs) const { return Items(toUL() ^ rhs.toUL()); }
	bool operator==(const Items &rhs) const { return contents == rhs.contents; }
	bool operator!=(const Items &rhs) const { return contents != rhs.contents; }
	void add(const EFood &food){ contents[static_cast<int>(food)] = 1; }
	template <typename T, typename... Args>
	void add(const T &food, Args... args){ add(food); add(args...); }
	void remove(const EFood &food){ contents[static_cast<int>(food)] = 0; }
	template <typename T, typename... Args>
	void remove(const T &food, Args... args){ remove(food); remove(args...); }
	void clear(){ contents.reset(); }
	bool contains(const EFood &food) const{ return contents[static_cast<int>(food)]; }
	bool empty() const{ return contents.none(); }
	int count() const { return contents.count(); }
	bool isMaterialOf(const Items &rhs) const { return (contents & rhs.contents) == contents; }
	unsigned long toUL() const { return contents.to_ulong(); }
	void print() const {
		cerr << contents.to_string() << endl; 
		for(int i = 0; i < 32; i++) cerr << (contents[i] ? EFood2Str[i] : "") << " ";
		cerr << endl;
	}
	class HashFunction {
	public:
		size_t operator()(const Items &items) const { return items.contents.to_ulong(); }
	};
private:
	bitset<32> contents;

};

Items str2Items(const std::string &s) {
	static const std::unordered_map<std::string, EFood> transform = {
		{std::string("DISH"), EFood::DISH},
		{std::string("BLUEBERRIES"), EFood::BLUEBERRIES},
		{std::string("ICE_CREAM"), EFood::ICE_CREAM},
		{std::string("STRAWBERRIES"), EFood::STRAWBERRIES},
		{std::string("CHOPPED_STRAWBERRIES"), EFood::CHOPPED_STRAWBERRIES},
		{std::string("DOUGH"), EFood::DOUGH},
		{std::string("CHOPPED_DOUGH"), EFood::CHOPPED_DOUGH},
		{std::string("CROISSANT"), EFood::CROISSANT},
		{std::string("RAW_TART"), EFood::RAW_TART},
		{std::string("TART"), EFood::TART},
	};
	Items items;
	auto &&foods = split(s, '-');
	for(auto &food: foods) {		
		if(auto &&found = transform.find(food); found != transform.end()) {
			items.add(found->second);
		}
	}
	return items;
}

class ILocation {
public:
	ILocation() {}
	virtual void print() const {
		cerr << loc.x << ' ' << loc.y << ' ';
	}
	Vec loc;
};

class Container: virtual public ILocation {
public:
	Container(): ILocation(), items() {}
	Container(const Container &rhs) { *this = rhs; }
	Container &operator=(const Container &rhs) {
		loc = rhs.loc;
		items = rhs.items;
		return *this;
	}
	virtual void print() const override {
		ILocation::print();
		items.print();
	}
	Items items;
};

class Window: virtual public ILocation {
public:
	Window(): ILocation() {}
};

class Maker: virtual public ILocation {
public:
	Maker(): ILocation() {}
	virtual bool isMaking() const = 0;
	unordered_map<Items, Items, Items::HashFunction> recipes;
};

class ChoppingBoard: virtual public Maker {
public:
	ChoppingBoard(): Maker() {}
	virtual bool isMaking() const override {
		return false;
	};
};

class Oven: virtual public Container, virtual public Maker {
public:
	Oven(): Container(), Maker(), timer(0) {}
	virtual bool isMaking() const override {
		if(items.empty()) return false;
		return recipes.find(items) == recipes.end(); // items is not product
	};
	virtual void print() const override {
		ILocation::print();
		items.print();
		cerr << "timer: " << timer << endl;
	}
	int timer;
};

class Kitchen {
public:
	Kitchen() {}
	shared_ptr<Window> window;
	shared_ptr<Container> dishWasher;
	vector<shared_ptr<Container>> containers;
	unordered_map<Items, shared_ptr<Maker>, Items::HashFunction> makers;
	unordered_map<Items, pair<Items, Items>, Items::HashFunction> mergeRecipes;
};

class Chef {
public:
	static function<void()> use(const Vec &loc) {
		return [loc]()  {
			cout << "USE " << loc.x << ' ' << loc.y << endl;
		};
	}
	static function<void()> wait() {
		return []() {
			cout << "WAIT" << endl;
		};
	}
	Vec loc;
	Items items;
};

