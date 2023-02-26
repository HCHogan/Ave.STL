#ifndef __MAX_HPP
#define __MAX_HPP

#include "./predefined_oops.hpp"
#include <initializer_list>
#include "iterator_traits.hpp"

namespace Ave {
	template<typename _ForwardIterator, typename _Compare>
	_ForwardIterator __max_element(_ForwardIterator __first, _ForwardIterator __last, _Compare __comp) {
		if(__first == __last) return __first;
		_ForwardIterator __result = __first;
		while(++__first != __last)
			if(__comp(__result, __first))
				__result = __first;
		return __result;
	}

	template<typename _ForwardIterator>
	inline _ForwardIterator max_element(_ForwardIterator __first, _ForwardIterator __last) {
		return __max_element(__first, __last, __iter_less_iter());
	}

	template<typename _Tp>
	inline _Tp max(std::initializer_list<_Tp> __l) {
		return *max_element(__l.begin(), __l.end());
	}				// 参数类型都一样的话就不用variadic templates, initializer_list<T>足矣.
	
	template<typename _ForwardIterator, typename _Compare>
	typename iterator_traits<_ForwardIterator>::value_type max(_ForwardIterator first, _ForwardIterator last, _Compare cmp) {
		return *__max_element(first, last, cmp);
	}
	
	/*
	 * 以下是variadic templates 实现的max
	 */

	int maximum(int n) {
		return n;
	}

	template<typename... Args>
	int max(int n, Args... args) {
		return max(n, maximum(args...));
	}
}

#endif
