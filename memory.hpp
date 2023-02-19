#ifndef __MEMORY_HPP
#define __MEMORY_HPP
#include "./iterator_traits.hpp"

namespace Ave {
	template<class Iterator, class T>
	void construct(Iterator iter, const T& x) {
		*iter = x;
		return;
	}

	template<class Iterator>
	void destroy(Iterator first, Iterator finish) {
		for(; first != finish; ++first) {
			
		}
	}

	template<class Iterator>
	void copy(Iterator start, Iterator end, Iterator des) {
		while(start != end) {
			*des = *start;
			++start;
			++des;
		}
	}

	template<class Iterator>
	Iterator uninitialized_copy(Iterator start, Iterator end, Iterator des) {
		copy(start, end, des);
		return des;
	}

	template<class Iterator>
	void copy_backward(Iterator start, Iterator end, Iterator des) {
		do {
			--des;
			--end;
			*des = *end;
		} while(end != start);
	}

	template<class Iterator, class T>
	void uninitialized_fill_n(Iterator first, size_t n, const T& x) {
		while(n--) {
			construct(first, x);
			++first;
		}
	}
}

#endif
