#include <iostream>

class String {
public:
	class Iterator {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = char;
		using pointer = char*;
		using reference = char&;
		Iterator(char *ptr);
		reference operator*();
		pointer operator->();
		Iterator &operator++();
		Iterator operator++(int);
		Iterator &operator--();
		Iterator operator--(int);
		friend bool operator==(const Iterator &lhs, const Iterator &rhs);
		friend bool operator!=(const Iterator &lhs, const Iterator &rhs);
		friend Iterator operator+(const Iterator &it, size_t n);
		friend Iterator operator-(const Iterator &it, size_t n);
		friend difference_type operator-(const Iterator &lhs, const Iterator &rhs);
	private:
		pointer ptr_;
	};
	class ConstIterator {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = const char;
		using pointer = const char*;
		using reference = const char&;
		ConstIterator(const char *ptr);
		reference operator*() const;
		pointer operator->() const;
		ConstIterator &operator++();
		ConstIterator operator++(int);
		ConstIterator &operator--();
		ConstIterator operator--(int);
		friend bool operator==(const ConstIterator &lhs, const ConstIterator &rhs);
		friend bool operator!=(const ConstIterator &lhs, const ConstIterator &rhs);
		friend ConstIterator operator+(const ConstIterator &it, size_t n);
		friend ConstIterator operator-(const ConstIterator &it, size_t n);
		friend difference_type operator-(const ConstIterator &lhs, const ConstIterator &rhs);
	private:
		pointer ptr_;
	};
	String();
	String(const String &s);
	String(const char *s);
	String(nullptr_t) = delete;
	~String();
	String &operator=(const String &rhs);
	String &operator=(const char *rhs);
	String &operator=(String &&rhs);
	String &operator=(nullptr_t) = delete;
	// Element access
	char &operator [](size_t pos);
	const char &operator [](size_t pos) const;
	char *data();
	const char *data() const;
	const char *c_str() const;
	// Iterators
	Iterator begin();
	ConstIterator begin() const;
	ConstIterator cbegin() const;
	Iterator end();
	ConstIterator end() const;
	ConstIterator cend() const;
	// Capacity
	size_t size() const;
	void reserve(size_t new_cap);
	size_t capacity() const;
	// Operations
	void clear();
	String &operator+=(const String &rhs);
	String &operator+=(const char *rhs);
	String &operator+=(char rhs);
	void resize(size_t new_size);
	void resize(size_t new_size, char ch);
	void swap(String &rhs);
	// Non-member functions
	friend String operator+(const String &lhs, const String &rhs);
	friend String operator+(const String &lhs, const char *rhs);
	friend String operator+(const String &lhs, char rhs);
	friend String operator+(const char *lhs, const String &rhs);
	friend String operator+(char lhs, const String &rhs);
	friend bool operator==(const String &lhs, const String &rhs);
	friend bool operator==(const String &lhs, const char *rhs);
	friend bool operator==(const char *lhs, const String &rhs);
	friend bool operator!=(const String &lhs, const String &rhs);
	friend bool operator!=(const String &lhs, const char *rhs);
	friend bool operator!=(const char *lhs, const String &rhs);
	friend bool operator<(const String &lhs, const String &rhs);
	friend bool operator<(const String &lhs, const char *rhs);
	friend bool operator<(const char *lhs, const String &rhs);
	friend bool operator>(const String &lhs, const String &rhs);
	friend bool operator>(const String &lhs, const char *rhs);
	friend bool operator>(const char *lhs, const String &rhs);
	friend bool operator<=(const String &lhs, const String &rhs);
	friend bool operator<=(const String &lhs, const char *rhs);
	friend bool operator<=(const char *lhs, const String &rhs);
	friend bool operator>=(const String &lhs, const String &rhs);
	friend bool operator>=(const String &lhs, const char *rhs);
	friend bool operator>=(const char *lhs, const String &rhs);
	// Input/output
	friend std::ostream &operator<<(std::ostream &os, const String &str);
	friend std::istream &operator>>(std::istream &is, String &str);
private:
	size_t size_;
	size_t capacity_;
	char *str_;
};
