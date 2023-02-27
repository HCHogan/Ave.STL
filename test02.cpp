#include <iterator>
#include <list>
#include "./list.hpp"
#include <iostream>

Ave::list<int> mylist;
Ave::list<int> mylist2{1, 2, 3};
std::list<int> stdlist;

int main() {
	for(int i = 0; i < 100; i++) mylist.push_back(i);
	std::cout << mylist.front() << std::endl;
	std::cout << mylist.back() << std::endl;
	for(auto it = mylist2.begin(); it != mylist2.end(); ++it) {
		std::cout << mylist2.end().node - it.node << std::endl;
		std::cout << *it << std::endl;
	}
	std::cout << "size: " << mylist2.size() << std::endl;
	// for(auto it = mylist.begin(); !(it == mylist.end()); ++it) {
		// std::cout << *it << std::endl;
	// }
	return 0;
}
