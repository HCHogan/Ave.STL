// <vector> -*- C++ -*-
//
// Copyright (C) 2023 Avenue Inc.
//

#ifndef __VECTOR
#define __VECTOR

#include <alloca.h>
#include <initializer_list>
#include <memory>
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
	
		vector(): start(0), finish(0), end_of_storage(0) { std::cout << "Ave::vector defalut constructed\n"; }

	public:
		iterator begin() const { return start; }
		iterator end() const { return finish; }

		reference front() { return *begin(); }
		reference back() { return *end() - 1;}

		size_type size() const { return size_type(end() - begin());}
		size_type capacity() const { return size_type(end_of_storage - begin()); }

		bool empty() const { return begin() == 0; }

		void pop_back() {
			--finish;
			destory(finish);	// TODO: destory()
		}

		void push_back(const T& x) {
			if(finish != end_of_storage) {
				construct(finish, x);		// TODO: construct()
				++finish;
			} else {
				insert_aux(end(), x);
			}
		}

		iterator erase(iterator position) {
			if(position + 1 != end()) copy(position+1, finish, position);	// TODO: copy()
		}

		reference operator[](size_type n){ return *(begin() + n); }

		static const int expand_rate = 2;
	

	protected:
		typedef Alloc allocator;

		void insert_aux(iterator position, const T& x);						// TODO: insert_aux()
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

		void allocate_and_fill(size_type n, const T& x) {
			iterator result = allocator::allocate(n);
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
			T x_copy = x;
		}
	}
};


#endif
