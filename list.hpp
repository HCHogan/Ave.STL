// <list> -*- C++ -*-
//
// Copyright (C) 2023 Avenue Inc.
//

#ifndef __LIST_HPP
#define __LIST_HPP

#include <stddef.h>
#include <iostream>
#include "./memory.hpp"
#include "./simple_allocator.hpp"
#include "./iterator_category.hpp"

namespace Ave {

	template<class T>
	class __list_node {
		T* prev;
		T* next;
		T data;
	};

	template<class T>
	class __list_iterator {
	public:
		typedef __list_iterator<T> _self;
		typedef __list_node<T> _node;
		
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ptrdiff_t difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		typedef __list_node<T>* node;

	public:
		
	};
		
	template<class T, class Alloc = simple_allocator<T>>
	class list {
	protected:
		typedef __list_node<T> list_node;

	public:
		typedef T value_type;
		typedef T* pointer;
		typedef __list_iterator<T> iterator;
		typedef T& reference;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		typedef list_node* link_type;

	};
};

#endif
