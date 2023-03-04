#include <iterator>
#include <list>
#include "./list.hpp"
#include <iostream>

Ave::list<int> mylist;
Ave::list<int> mylist2{1, 2, 3};
std::list<int> stdlist;

int main() {
	for(int i = 100; i >= 1; --i) {
		mylist.push_back(i);
		stdlist.push_back(i);
	}

	mylist.sort();

	for(auto it = mylist.begin(); it != mylist.end(); ++it) {
		std::cout << *it << std::endl;
	}

	return 0;
}
