// #include "api.h"


class Producerx {
public:
	class Chop {
	public:
		static Items chop(const Items a) {
			return getChopTable().at(a);
		}
	private:
		static const std::unordered_map<Items, Items> &getChopTable() {
			static const std::unordered_map<Items, Items> chopTable = {
				{ Items::STRAWBERRIES, Items::CHOPPED_STRAWBERRIES },
				{ Items::DOUGH, Items::CHOPPED_DOUGH },
			};
			return chopTable;
		}
	};
	class Bake {
	public:
		static Items bake(const Items a) {
			return getBakeTable().at(a);
		}
	private:
		static const std::unordered_map<Items, Items> &getBakeTable() {
			static const std::unordered_map<Items, Items> bakeTable = {
				{ Items(EFood::DOUGH), Items(EFood::CROISSANT) },
				{ Items(EFood::RAW_TART), Items(EFood::TART) },
			};
			return bakeTable;
		}
	};
	class Merge {
	public:
		static Items merge(const Items &a, const Items &b) {
			return getMergeTable().at(std::pair<Items, Items>(a, b));
		}
	private:
		static const std::unordered_map<std::pair<Items, Items>, Items> &getMergeTable() {
			static const std::unordered_map<std::pair<Items, Items>, Items> mergeTable = {
				{ std::pair<Items, Items>(Items(EFood::BLUEBERRIES), Items(EFood::DOUGH)), Items(EFood::RAW_TART) },
				{ std::pair<Items, Items>(Items(EFood::DOUGH), Items(EFood::BLUEBERRIES)), Items(EFood::RAW_TART) },
			};
			return mergeTable;
		}
	};
};