#ifndef __MOVE_HPP
#define __MOVE_HPP

template<typename T> constexpr T&&
forward(typename Ave::remove_reference<T>::type& t) noexcept {
	return static_cast<T>(t);
}

template<typename T> constexpr T&&
forward(typename Ave::remove_reference<T>::type&& t) noexcept {
	// static_assert(!std::is_lvalue_reference<T>::type&& t);
	return static_cast<T&&>(t);
}

#endif
