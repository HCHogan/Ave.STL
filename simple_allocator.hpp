#include <new>
#include <stddef.h>

namespace Ave{
	template <typename T>
	class simple_allocator {
	public:
		T* allocate(size_t size, size_t extra) {
			return new T[size];
		}

		void* deallocate(T* ptr, size_t extra) {
			delete [] ptr;
			return NULL;
		}
	};
}
