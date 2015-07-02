#include <iostream>
#include <string>

#include "list-generic-c++.h"

#define check(c) { std::cerr << (c ? "passed: " : "FAILED: ") << #c << std::endl; }

int main(int argc, char *argv[])
{
	List<std::string> list;

	check(list.size() == 0);
	list.insert(std::string("abc"));
	check(list.size() == 1);
	check(list.contains(std::string("abc")));
	check(!list.contains(std::string("def")));
	check(list.get(0) == std::string("abc"));
	list.insert(std::string("def"));
	check(list.size() == 2);
	check(list.get(0) == std::string("def"));
	list.remove(std::string("abc"));
	check(!list.contains(std::string("abc")));

	return 0;
}
