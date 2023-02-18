#include <initializer_list>
#include <stddef.h>
#include <iostream>
#include "./simple_allocator.hpp"

namespace Ave{
	template<class T, class Alloc = simple_allocator<T>>
	class vector {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T* iterator;
		typedef T& reference;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
	
		vector(): start(0), finish(0), end_of_storage(0) { std::cout << "Ave::vector defalut constructed\n"; }

	public:
		iterator begin() const { return start; }
		iterator end() const { return finish; }

		reference front() { return *begin(); }
		reference back() { return *end() - 1;}

		size_type size() const { return size_type(end() - begin());}
		size_type capacity() const { return size_type(end_of_storage - begin()); }

		bool empty() const { return begin() == 0; }

		reference operator[](size_type n){ return *(begin() + n); }

		static const int expand_rate = 2;
	
	protected:
		void fill_initialize(size_type n, const T& value) {
			start = allocate_and_fill(n, value);
			finish = start + n;
			end_of_storage = finish;
		}

	protected:
		typedef Alloc allocator;

	protected:
		iterator start;
		iterator finish;
		iterator end_of_storage;
	};
};
