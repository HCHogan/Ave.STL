#include <new>
#include <stddef.h>

namespace Ave{
	template <typename T>
	class simple_allocator {
	public:
		T* allocate(size_t size) {
			return new T[size];
		}

		void* deallocate(T* ptr) {
			delete [] ptr;
			return NULL;
		}
	};
}
