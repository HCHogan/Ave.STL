#include "./vector.hpp"
#include "iostream"
#include <memory>
#include <vector>

int a = 1;

int main() {
	Ave::vector<int> myvec;
	Ave::vector<char> mycharvec(100);
	Ave::vector<int> myintvee(100, a);

	std::cout << "size: " << myvec.size() << std::endl;

	for(int i = 0; i < 100; i++) myvec.push_back(i);
	for(int i = 0; i < 100; i++) std::cout << myvec[i] << std::endl;
	
	std::cout << "size: " << myvec.size() << std::endl;
	std::cout << "capacity: " << myvec.capacity() << std::endl;
	std::cout << myvec[0] << std::endl;

	return 0;
}
