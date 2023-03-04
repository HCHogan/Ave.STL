// <list> -*- C++ -*-
//
// Copyright (C) 2023 Avenue Inc.
//

#ifndef __LIST_HPP
#define __LIST_HPP

#include <alloca.h>
#include <stddef.h>
#include <iostream>
#include "./memory.hpp"
#include "./simple_allocator.hpp"
#include "./iterator_category.hpp"
#include <initializer_list>

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

		reference operator*() const { return (*node).data; }
		pointer operator->() const { return &(operator*()); }		// operator->本来的作用对象是指针, 这是operator->的标准做法

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
		
	template<class T, class Alloc = simple_allocator2<T>>
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
			return (link_type)allocator::allocate();
		}

		link_type create_node(const T& x) {
			link_type p = get_node();
			p->data = x;
			return p;
		}

		void destroy_node(link_type p) {
			destroy(&p->data);
			put_node(p);
		}

		void put_node(link_type p) {
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

		list(const std::initializer_list<T>& __l) {
			empty_initializer();
			for(auto x : __l) push_back(x);
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
			tmp->next = position.node;
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

		// iterator erase(const T& x) {
			// iterator tmp = find(begin(), end(), x);
			// erase(tmp);
		// }

		// 清空整个列表
		void clear() {
			link_type cur = node->next;
			while(cur != node) {
				link_type tmp = cur;
				cur = cur->next;
				destroy_node(tmp);
			}
			node->next = node;
			node->prev = node;
		}

		// 移除所有值为x的节点
		void remove(const T& x) {
			iterator cur = begin();
			iterator last = end();
			while(cur != last) {
				iterator tmp = cur;
				++cur;
				if(&tmp == x)
					erase(tmp);
			}
		}

		void unique() {
			iterator start = begin();
			iterator finish = end();
			if(start == finish) return;
			iterator next = start;
			while(++next != finish) {
				if(&next == &start) erase(next);
				else start = next;
			}
		}

		size_type size() {
			size_type cnt = 0;
			for(iterator it = begin(); it != end(); ++it) ++cnt;
			return cnt;
		}
	
	protected:
		// 将first到last的内容放到position之前
		void transfer(iterator position, iterator first, iterator last) {
			if(position == last) return;
			last.node->prev->next = position.node;
			first.node->prev->next = last.node;
			position.node->prev->next = first.node;
			link_type tmp = position.node->prev;
			position.node->prev = last.node->prev;
			last.node->prev = first.node->prev;
			first.node->prev = tmp;
		}
	
	public:
		// 将x接合于position所指位置之前 x必须不同于*this
		void splice(iterator position, list& x) {
			if(!x.empty())
			transfer(position, x.begin(), x.end());
		}

		// 吧i所指位置的元素接在position之前
		void splice(iterator position, list&, iterator i) {
			if(i == position) return;
			iterator j = i;
			++j;
			transfer(position, i, j);
		}

		// 吧first到last接到list x的 position前面
		void splice(iterator position, list& , iterator first, iterator last) {
			if(first != last)
				transfer(position, first, last);
		}

	public:
		void push_back(const T& x) {
			insert(end(), x);
		}

		void push_front(const T& x) {
			insert(begin(), x);
		}

		void sort();
		void merge(list<T, Alloc>& x);
		void reverse();

		void swap_elem(iterator lhs, iterator rhs) {
			link_type one = lhs.node->prev;
			link_type two = lhs.node->next;
			link_type three = rhs.node->prev;
			link_type four = rhs.node->next;
			lhs.node->next = four;
			lhs.node->prev = three;
			rhs.node->next = two;
			rhs.node->prev = one;
		}

		void swap(list<T, Alloc>& x) {
			auto it = begin();
			splice(begin(), x);
			splice(x.begin(), *this, it, end());
		}
	
	protected:
		link_type node;
	};

	// merge list x on this (two sorted list)
	template<class T, class Alloc>
	void list<T, Alloc>::merge(list<T, Alloc>& x) {
		iterator first1 = begin();
		iterator last1 = end();
		iterator first2 = x.begin();
		iterator last2 = x.end();

		while(first1 != last1 && first2 != last2) {
			if(*first2 < *first1) {
				iterator next = first2;
				transfer(first1, first2, ++next);
				first2 = next;
			} else {
				++first1;
			}
		}

		if(first2 != last2)
			transfer(last1, first2, last2);
		// if x left > this, merge the left part onto x
	}

	template<typename T, typename Alloc>
	void list<T, Alloc>::reverse() {
		if(node->next == node || node->next->next == node)
			return;

		iterator first = begin();
		++first;

		while(first != end()) {
			iterator old = first;
			++first;
			transfer(begin(), old, first);
		}
	}

	template<class T, class Alloc>
	void list<T, Alloc>::sort() {
		if(node->next->next == node && node->next == node)
			return;
		list<T, Alloc> temp;
		list<T, Alloc> counter[64];
		int fill = 0;

		while(!empty()) {
			temp.splice(temp.begin(), *this, begin());
			int i = 0;
			while(i < fill && !counter[i].empty()) {
				counter[i].merge(temp);
				temp.swap(counter[i++]);
			}
			temp.swap(counter[i]);
			if(i == fill) ++fill;
		}

		for(int i = 1; i < fill; ++i)
			counter[i].merge(counter[i - 1]);

		swap(counter[fill - 1]);
	}
};


#endif
