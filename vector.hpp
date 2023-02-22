// <vector> -*- C++ -*-
//
// Copyright (C) 2023 Avenue Inc.
//

#ifndef __VECTOR__HPP
#define __VECTOR__HPP

#include <stddef.h>
#include <iostream>
#include "./memory.hpp"
#include "./simple_allocator.hpp"
// BOGUS: what to include?

namespace Ave{
	template<class T, class Alloc = simple_allocator<T>>
	class vector {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T* iterator;
		typedef T& reference;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
	
		vector(): start(0), finish(0), end_of_storage(0) { 
			std::cout << "Ave::vector defalut constructed\n"; 
		}

		vector(size_type n, const T& value) {
			fill_initialize(n, value);
			std::cout << "Ave::vector fill_initialize constructed\n";
		}

		vector(int n, const T& value) {
			fill_initialize(n, value);
			std::cout << "Ave::vector fill_initialize constructed\n";
		}

		vector(long n, const T& value) {
			fill_initialize(n, value);
			std::cout << "Ave::vector fill_initialize constructed\n";
		}

		explicit vector(size_type n) {
			fill_initialize(n, T());
			std::cout << "Ave::vector fill_initialize constructed\n";
		}

		~vector() {
			destroy(start, finish);
			deallocate();
			std::cout << "Ave::vector destroyed\n";
		}

	public:
		iterator begin() const { return start; }
		iterator end() const { return finish; }

		reference front() { return *begin(); }
		reference back() { return *end() - 1; }

		size_type size() const { return size_type(end() - begin()); }
		size_type capacity() const { return size_type(end_of_storage - begin()); }

		bool empty() const { return begin() == 0; }

		void clear() {
			erase(begin(), end());
		}

		void pop_back() {
			--finish;
			destroy(finish);	// TODO: destroy()
		}

		void push_back(const T& x) {
			if(finish != end_of_storage) {
				construct(finish, x);		// TODO: construct()
				++finish;
			} else {
				insert_aux(end(), x);
			}
		}

		iterator erase(iterator first, iterator last) {
			iterator it = copy(last, finish, first);		// TODO: copy
			destroy (it, finish);
			finish = finish - (last - first);
			return first;
		}

		iterator erase(iterator position) {
			if(position + 1 != end()) copy(position+1, finish, position);	// TODO: copy()
			--finish;
			destroy(finish);
			return position;
		}

		reference operator[](size_type n){ return *(begin() + n); }

		static const int expand_rate = 2;
	

	protected:
		typedef Alloc allocator;

		void insert_aux(iterator position, const T& x);
		void deallocate() {
			if(start)
				allocator::deallocate(start, end_of_storage - start);
		}

	protected:
		void fill_initialize(size_type n, const T& value) {
			start = allocate_and_fill(n, value);							
			finish = start + n;
			end_of_storage = finish;
		}

		iterator allocate_and_fill(size_type n, const T& x) {
			iterator result = allocator::allocate(sizeof(T) * n, 0);
			uninitialized_fill_n(result, n, x);								// TODO: uninitialized_fill_n()
			return result;
		}
		
	protected:
		iterator start;
		iterator finish;
		iterator end_of_storage;
	};

	template <class T, class Alloc>
	void vector<T, Alloc>::insert_aux(iterator position, const T& x) {
		if(finish != end_of_storage) {
			construct(finish, *(finish - 1));
			++finish;
			T temp = x;
			copy_backward(position, finish - 2, finish - 1);
			*position = temp;
		} else {
			size_type old_size = size();
			size_type len = old_size != 0 ? expand_rate*old_size : 1;
			// if 0, 1 else rate * old_size;
			iterator new_start = Alloc::allocate(sizeof(T) * len,0);
			iterator new_finish = new_start + old_size;
			// copy the old container to the new one
			try {
				uninitialized_copy(start, position, new_start);
				construct(new_finish, x);
				++new_finish;
			} catch(...) {
				destroy(new_start, new_finish);
				allocator::deallocate(new_start, len);
				throw;
			}
			destroy(begin(), end());
			deallocate();
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len;
		}
	}
};


#endif
