#ifndef __ARRAY_HPP
#define __ARRAY_HPP

#include "./memory.hpp"
#include "./iterator_category.hpp"
#include <features.h>
#include <stddef.h>

namespace Ave {
	template<typename T, size_t N>
	struct array {
		typedef T			value_type;
		typedef T*			pointer;		// native pointer
		typedef T&			reference;
		typedef value_type*	iterator;
		typedef size_t		size_type;
		typedef random_access_iterator_tag iterator_category;

		// no ctor and dtor
		// support for zero-sized arrays mandatory
		value_type _instance[N ? N : 1];

		iterator begin() {
			return iterator(&_instance[0]);
		}

		iterator end() {
			return iterator(&_instance[N]);
		}

		size_type size() {
			return N;
		}

		reference operator[](int n) {
			return _instance[n];
		}
	};
	
}

#endif
