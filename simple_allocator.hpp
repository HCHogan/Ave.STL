#include <new>
#include <stddef.h>

namespace Ave{
	template <typename T>
	class simple_allocator {
	public:
		static T* allocate(size_t size, void* extra) {
			return static_cast<T*>(::operator new(size));
		}

		static void deallocate(T* ptr, void* extra) {
			delete [] ptr;
		}
	};
}
