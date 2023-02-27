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
	struct __list_node {
		__list_node<T>* prev;
		__list_node<T>* next;
		T data;
	};

	template<class T>
	struct __list_iterator {
	public:
		typedef __list_iterator<T> self;
		typedef __list_node<T>* link_type;
		
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ptrdiff_t difference_type;
		typedef bidirectional_iterator_tag iterator_category;

		link_type node;

		reference operator*() const { return node->data; }
		pointer operator->() const { return &(operator*()); }		// operator->本来的作用对象是指针

		__list_iterator(const __list_iterator<T>& it) : node(it.node) {}

		__list_iterator(const link_type& x) : node(x) { }

		__list_iterator<T>& operator++() {
			node = node->next;
			return *this;
		}

		__list_iterator<T> operator++(int) {
			__list_iterator<T> temp = *this;		// 不会调用重载过的operator*因为编译器先遇到了=,解释为赋值构造
			++*this;
			return temp;
		}

		__list_iterator<T>& operator--() {
			node = node->prev;
			return *this;							// 并不会唤起什么
		}

		__list_iterator<T> operator--(int) {
			__list_iterator<T> temp = *this;
			--*this;
			return temp;
		}

		__list_iterator<T>& operator+(int n) {
			while(n) {
				++*this;
			}
			return *this;
		}

		__list_iterator<T>& operator-(int n) {
			while(n) {
				--*this;
			}
			return *this;
		}

		bool operator==(const self& x) const {
			return node == x.node;
		}

		bool operator!=(const self& x) const {
			return node != x.node;
		}
		
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
		typedef Alloc allocator;

		typedef list_node* link_type;

		link_type get_node() {
			return (link_type)allocator::allocate(sizeof(list_node));
		}

		link_type create_node(const T& x) {
			link_type p = get_node();
			p->data = x;
			return p;
		}

		void destroy_node(link_type p) {
			destroy(&p->data);
			allocator::deallocate(p);
		}

		void empty_initializer() {
			node = get_node();
			node->next = node;
			node->prev = node;
		}

		list() {
			empty_initializer();
		}

		iterator begin() {
			return node->next;
		}

		iterator end() {
			return node;
		}

		bool empty() {
			return node->next == node;
		}

		reference front() {
			return *begin();
		}

		reference back() {
			return *(--end());
		}

		iterator insert(iterator position, const T& x) {
			link_type tmp = create_node(x);
			tmp->next = position.node->next;
			tmp->prev = position.node->prev;
			position.node->prev->next = tmp;
			position.node->prev = tmp;
			return tmp;
		}

		iterator erase(iterator position) {
			link_type next_node = position.node->next;
			link_type prev_node = position.node->prev;
			prev_node->next = next_node;
			next_node->prev = prev_node;
			destroy_node(position);
			return next_node;
		}
		
		iterator find(iterator start, iterator finish, const T& x) {
			while(start != finish) {
				if(start.node->data == x)
					return start;
				++start;
			}
			return start;
		}

		iterator erase(const T& x) {
			iterator tmp = find(begin(), end(), x);
			erase(tmp);
		}

		size_type size() {
			size_type cnt = 0;
			for(iterator it = begin(); it != end(); ++it) ++cnt;
			return cnt;
		}

	public:
		void push_back(const T& x) {
			insert(end(), x);
		}

		void push_front(const T& x) {
			insert(begin(), x);
		}
	
	protected:
		link_type node;
	};
};

#endif
