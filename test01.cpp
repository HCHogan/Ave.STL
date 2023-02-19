#include "./vector.hpp"
#include "iostream"
#include <memory>
#include <vector>

int main() {
	Ave::vector<int> myvec;
	std::vector<int> stdvec;
	std::cout << sizeof(myvec) << std::endl;
	std::cout << sizeof(stdvec) << std::endl;
	return 0;
}
