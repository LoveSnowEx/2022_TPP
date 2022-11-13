#include <bits/stdc++.h>
#include "string.h";
// using namespace std;

template<typename Iterator, typename Compare>
void sort(Iterator first, Iterator last, Compare compare) {
	if(last-first < 2) return;
	using T = std::remove_reference_t<decltype(*first)>;
	size_t size = last-first;
	auto mid = first+size/2;
	sort(first, mid, compare);
	sort(mid, last, compare);
	std::vector<T> res;
	res.reserve(size);
	auto l = first, r = mid;
	while(l < mid && r < last) {
		if(compare(*l, *r) < 0) res.emplace_back(*l++);
		else res.emplace_back(*r++);
	}
	while(l < mid) res.emplace_back(*l++);
	while(r < last) res.emplace_back(*r++);
	std::copy(res.begin(), res.end(), first);
}

// template<typename Iterator, typename Compare>
// void sort(Iterator first, size_t size, Compare compare) {
// 	sort(first, first+size, compare);
// }

int main() {
	return 0;
}