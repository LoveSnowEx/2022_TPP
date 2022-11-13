#include "String.h"
#include <cstring>  // for strlen, strcmp

constexpr size_t DEFAULT_CAPACITY = 16;

String::String(): size_(0), capacity_(DEFAULT_CAPACITY), str_(new char[capacity_]()) {}

String::String(const String &s): size_(s.size_), capacity_(s.capacity_), str_(new char[capacity_]()) {
	if(this == &s) return;
	std::copy(s.begin(), s.end(), begin());
	*end() = '\0';
}

String::String(const char *s): size_(strlen(s)), capacity_(std::max(DEFAULT_CAPACITY, size_+1)), str_(new char[capacity_]()) {
	std::copy(s, s+size_, begin());
	*end() = '\0';
}

String::~String() {
	delete []str_;
};

String &String::operator=(const String &rhs) {
	if(this == &rhs) return *this;
	resize(rhs.size());
	std::copy(rhs.begin(), rhs.end(), begin());
	*end() = '\0';
	return *this;
}

String &String::operator=(const char *rhs) {
	size_t size = strlen(rhs);
	resize(size);
	std::copy(rhs, rhs+size, begin());
	*end() = '\0';
	return *this;
}

String &String::operator=(String &&rhs) {
	if(this == &rhs) return *this;
	str_ = std::move(rhs.str_);
	return *this;
}

char &String::operator[](size_t pos) { return data()[pos]; }

const char &String::operator[](size_t pos) const { return data()[pos]; }

char *String::data() { return str_; };

const char *String::data() const { return str_; };

const char *String::c_str() const { return data(); };

String::Iterator String::begin() {
	return String::Iterator(data());
}

String::ConstIterator String::begin() const {
	return cbegin();
}

String::ConstIterator String::cbegin() const {
	return String::ConstIterator(data());
}

String::Iterator String::end() {
	return String::Iterator(data()+size());
}

String::ConstIterator String::end() const {
	return cend();
}

String::ConstIterator String::cend() const {
	return String::ConstIterator(data()+size());
}

size_t String::size() const { return size_; }

void String::reserve(size_t new_cap) {
	if(new_cap > capacity_) {
		while(capacity_ < new_cap) capacity_ *= 2;
		char *new_str = new char[capacity_]();
		std::copy(begin(), end(), new_str);
		delete []str_;
		str_ = new_str;
		*end() = '\0';
		return;
	}
}

size_t String::capacity() const { return capacity_; }

void String::clear() { resize(0); }

String &String::operator+=(const String &rhs) {
	size_t old_size = size_;
	resize(size() + rhs.size());
	std::copy(rhs.begin(), rhs.end(), begin()+old_size);
	*end() = '\0';
	return *this;
}

String &String::operator+=(const char *rhs) {
	size_t old_size = size_, rhs_size = strlen(rhs);
	resize(old_size + rhs_size);
	std::copy(rhs, rhs+rhs_size, begin()+old_size);
	*end() = '\0';
	return *this;
}

String &String::operator+=(char ch) {
	// *end() = ch;
	resize(size_+1);
	*(end()-1) = ch;
	*end() = '\0';
	return *this;
}

void String::resize(size_t new_size) {
	resize(new_size, '\0');
}

void String::resize(size_t new_size, char ch) {
	size_t old_size = size();
	reserve(new_size+1);
	size_ = new_size;
	if(new_size > old_size) std::fill(begin()+old_size, end(), ch);
	*end() = '\0';
}

void String::swap(String &rhs) {
	std::swap(size_, rhs.size_);
	std::swap(capacity_, rhs.capacity_);
	std::swap(str_, rhs.str_);
}

String operator+(const String &lhs, const String &rhs) {
	String tmp(lhs);
	return tmp += rhs;
}

String operator+(const String &lhs, const char *rhs) {
	String tmp(lhs);
	return tmp += rhs;
}

String operator+(const String &lhs, char rhs) {
	String tmp(lhs);
	return tmp += rhs;
}

String operator+(const char *lhs, const String &rhs) {
	String tmp(lhs);
	return tmp += rhs;
}

String operator+(char lhs, const String &rhs) {
	String tmp;
	tmp += lhs;
	return tmp += rhs;
}

bool operator==(const String &lhs, const String &rhs) {
	return strcmp(lhs.data(), rhs.data()) == 0;
}

bool operator==(const String &lhs, const char *rhs) {
	return strcmp(lhs.data(), rhs) == 0;
}

bool operator==(const char *lhs, const String &rhs) {
	return strcmp(lhs, rhs.data()) == 0;
}

bool operator!=(const String &lhs, const String &rhs) {
	return !(lhs == rhs);
}

bool operator!=(const String &lhs, const char *rhs) {
	return !(lhs == rhs);
}

bool operator!=(const char *lhs, const String &rhs) {
	return !(lhs == rhs);
}

bool operator<(const String &lhs, const String &rhs) {
	return strcmp(lhs.data(), rhs.data()) < 0;
}

bool operator<(const String &lhs, const char *rhs) {
	return strcmp(lhs.data(), rhs) < 0;
}

bool operator<(const char *lhs, const String &rhs) {
	return strcmp(lhs, rhs.data()) < 0;
}

bool operator>(const String &lhs, const String &rhs) {
	return strcmp(lhs.data(), rhs.data()) > 0;
}

bool operator>(const String &lhs, const char *rhs) {
	return strcmp(lhs.data(), rhs) > 0;
}

bool operator>(const char *lhs, const String &rhs) {
	return strcmp(lhs, rhs.data()) > 0;
}

bool operator<=(const String &lhs, const String &rhs) {
	return !(lhs > rhs);
}

bool operator<=(const String &lhs, const char *rhs) {
	return !(lhs > rhs);
}

bool operator<=(const char *lhs, const String &rhs) {
	return !(lhs > rhs);
}

bool operator>=(const String &lhs, const String &rhs) {
	return !(lhs < rhs);
}

bool operator>=(const String &lhs, const char *rhs) {
	return !(lhs < rhs);
}

bool operator>=(const char *lhs, const String &rhs) {
	return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &os, const String &str) {
	return os << str.data();
}

std::istream &operator>>(std::istream &is, String &str) {
	str.clear();
	char ch;
	while(is.good()) {
		ch = is.peek();
		if(ch == -1 || !isspace(ch)) break;
		is.ignore();
	}
	while(is.good()) {
		ch = is.peek();
		if(ch == -1 || isspace(ch)) break;
		str += ch;
		is.ignore();
	}
	return is;
}

//------------------------Iterator------------------------//

String::Iterator::Iterator(char *ptr): ptr_(ptr) {}

String::Iterator::reference String::Iterator::operator*() {
	return *ptr_;
}

String::Iterator::pointer String::Iterator::operator->() {
	return ptr_;
}

String::Iterator &String::Iterator::operator++() {
	++ptr_;
	return *this;
}

String::Iterator String::Iterator::operator++(int) {
	String::Iterator tmp = *this;
	++ptr_;
	return tmp;
}

String::Iterator &String::Iterator::operator--() {
	--ptr_;
	return *this;
}
String::Iterator String::Iterator::operator--(int) {
	String::Iterator tmp = *this;
	--ptr_;
	return tmp;
}

bool operator==(const String::Iterator &lhs, const String::Iterator &rhs) {
	return lhs.ptr_ == rhs.ptr_;
}

bool operator!=(const String::Iterator &lhs, const String::Iterator &rhs) {
	return lhs.ptr_ != rhs.ptr_;
}

String::Iterator operator+(const String::Iterator &it, size_t n) {
	return String::Iterator(it.ptr_+n);
}

String::Iterator operator-(const String::Iterator &it, size_t n) {
	return String::Iterator(it.ptr_-n);
}

String::Iterator::difference_type operator-(const String::Iterator &lhs, const String::Iterator &rhs) {
	return lhs.ptr_ - rhs.ptr_;
}

//------------------------Const Iterator------------------------//

String::ConstIterator::ConstIterator(const char *ptr): ptr_(ptr) {}

String::ConstIterator::reference String::ConstIterator::operator*() const {
	return *ptr_;
}

String::ConstIterator::pointer String::ConstIterator::operator->() const {
	return ptr_;
}

String::ConstIterator &String::ConstIterator::operator++() {
	++ptr_;
	return *this;
}

String::ConstIterator String::ConstIterator::operator++(int) {
	String::ConstIterator tmp = *this;
	++ptr_;
	return tmp;
}

String::ConstIterator &String::ConstIterator::operator--() {
	--ptr_;
	return *this;
}

String::ConstIterator String::ConstIterator::operator--(int) {
	String::ConstIterator tmp = *this;
	--ptr_;
	return tmp;
}

bool operator==(const String::ConstIterator &lhs, const String::ConstIterator &rhs) {
	return lhs.ptr_ == rhs.ptr_;
}

bool operator!=(const String::ConstIterator &lhs, const String::ConstIterator &rhs) {
	return lhs.ptr_ != rhs.ptr_;
}

String::ConstIterator operator+(const String::ConstIterator &it, size_t n) {
	return String::ConstIterator(it.ptr_+n);
}

String::ConstIterator operator-(const String::ConstIterator &it, size_t n) {
	return String::ConstIterator(it.ptr_-n);
}

String::Iterator::difference_type operator-(const String::ConstIterator &lhs, const String::ConstIterator &rhs) {
	return lhs.ptr_ - rhs.ptr_;
}
