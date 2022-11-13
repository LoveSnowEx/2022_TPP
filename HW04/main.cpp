// power by import magic DC
#include <bits/stdc++.h>
#include "String.h"

int main() {
	using namespace std;
	
	String s1, s2("abc"), s3(s2);
	cout << "------constructor-----\n";
	cout << "s1(): " << s1 << '\n';
	cout << "s2(\"abc\"): " << s2 << '\n';
	cout << "s3(s2): " << s3 << '\n';
	cout << "------information----\n";
	cout << "s3.size(): " << s3.size() << '\n';
	cout << "s3.c_ctr(): " << s3.c_str() << '\n';
	cout << "-------access--------\n";
	cout << "s3[2]: " << s3[2] << '\n';
	cout << "s3[2] = 'd';\n";
	s3[2] = 'd';
	cout << "s3: " << s3 << '\n';
	cout << "-----operator+=------\n";
	cout << "s2 += s3;\n";
	s2 += s3;
	cout << "s2: " << s2 << '\n';
	cout << "----copy assignment----\n";
	cout << "s1 = s3;\n";
	s1 = s3;
	cout << "s1: " << s1 << '\n';
	cout << "----------swap--------\n";
	cout << "s1: " << s1 << '\n';
	cout << "s1.size(): " << s1.size() << '\n';
	cout << "s2: " << s2 << '\n';
	cout << "s2.size(): " << s2.size() << '\n';
	cout << '\n';
	cout << "s1.swap(s2);\n";
	s1.swap(s2);
	cout << '\n';
	cout << "s1: " << s1 << '\n';
	cout << "s1.size(): " << s1.size() << '\n';
	cout << "s2: " << s2 << '\n';
	cout << "s2.size(): " << s2.size() << '\n';
	cout << "--------plus----------\n";
	cout << "s1: " << s1 << '\n';
	cout << "s2: " << s2 << '\n';
	cout << "s3: " << s3 << '\n';
	cout << "s1 + ',' + ' ' + s2 + \", \" + s3: " << s1 + ',' + ' ' + s2 + ", " + s3 << '\n';
	cout << "-----relational-------\n";
	cout << "s1: " << s1 << '\n' << "s2: " << s2 << '\n';
	cout << "s1 == s2: " << ((s1 == s2) ? "True" : "False") << '\n';
	cout << "s1 != s2: " << ((s1 != s2) ? "True" : "False") << '\n';
	cout << "s1 < s2: " << ((s1 < s2) ? "True" : "False") << '\n';
	cout << "s1 <= s2: " << ((s1 <= s2) ? "True" : "False") << '\n';
	cout << "s1 > s2: " << ((s1 > s2) ? "True" : "False") << '\n';
	cout << "s1 >= s2: " << ((s1 >= s2) ? "True" : "False") << '\n';
	cout << "-----iostream-------\n";
	cout << "stringstream ss(\"123456789 12345\\n6789\");\n";
	stringstream ss("123456789 12345\n6789");
	cout << "ss >> s1 >> s2 >> s3;\n";
	ss >> s1 >> s2 >> s3;
	cout << "s1: " << s1 << '\n';
	cout << "s2: " << s2 << '\n';
	cout << "s3: " << s3 << '\n';
	cout << "--------clear---------\n";
	cout << "s3.clear();\n";
	s3.clear();
	cout << "s3.size(): " << s3.size() << '\n';
	cout << "s3.c_ctr(): " << s3.c_str() << '\n';
	return 0;
}
