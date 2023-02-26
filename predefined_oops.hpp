struct _Iter_less_iter {
	template<typename _Iterator1, typename _Iterator2>
	bool operator()(_Iterator1 __it1, _Iterator2 __it2) const {
		return *__it1 < *__it2;
	}
};

inline _Iter_less_iter __iter_less_iter() {
	return _Iter_less_iter();
}
