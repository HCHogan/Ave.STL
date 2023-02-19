#include <cstddef>
namespace Ave {
	template<class T>
	struct iterator_traits {
		typedef typename T::value_type value_type;
		typedef typename T::difference_type difference_type;
		typedef typename T::iterator_category iterator_category;
		typedef typename T::pointer pointer;
		typedef typename T::reference reference;
	};

	// 以下是non-class iterator的偏特化
	template<class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template<class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;
	};
}
