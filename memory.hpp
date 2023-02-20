#ifndef __MEMORY_HPP
#define __MEMORY_HPP
#include "./iterator_traits.hpp"

namespace Ave {
	template<class T1, class T2>
	void construct(T1* p, const T2& x) {
		new(p) T1(x);
		return;
	}

	template<class T>
	void construct(T* p) {
		new(p) T();
		return;
	}

	template<class T>
	void destroy(T* first, T* finish) {
		for(; first != finish; ++first) {
			first->~T();
		}
	}

	template<class T>
	void destroy(T* p) {
		p->~T1();
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
