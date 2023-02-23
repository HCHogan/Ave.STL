#include <list>
#include "./list.hpp"
#include <iostream>

Ave::list<int> mylist;
std::list<int> stdlist;

int main() {
	std::cout << sizeof(mylist) << std::endl;
	std::cout << sizeof(stdlist) << std::endl;

	return 0;
}
