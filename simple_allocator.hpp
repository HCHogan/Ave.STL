#include <new>
#include <stddef.h>

namespace Ave{
	template <typename T>
	class simple_allocator {
	public:
		static T* allocate(size_t size, size_t extra = 0) {
			return static_cast<T*>(::operator new(size));
		}

		static void deallocate(T* ptr, size_t extra = 0) {
			delete [] ptr;
		}
	};

	template <typename T>
	class simple_allocator2 {
	public:
		static T* allocate(size_t size = 1) {
			return static_cast<T*>(new T[size]);
		}

		static void deallocate(T* p) {
			delete(p);
		}
	};
}
