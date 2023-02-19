#include "./vector.hpp"
#include "iostream"
#include <memory>
#include <vector>

int main() {
	Ave::vector<int> myvec;
	Ave::vector<char> mycharvec(100);

	myvec.push_back(1);

	std::cout << myvec[0] << std::endl;
	std::cout << mycharvec.size() << std::endl;

	return 0;
}
