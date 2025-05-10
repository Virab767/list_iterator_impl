#pragma once
#include <iostream>
#include <iterator>
#include <cstddef>

template <typename T>
	class my_list{
private:
	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node(const T& value) :data(value) , next(nullptr),prev(nullptr){}
	};
	
	Node* head;
	Node* tail;
	size_t size;
	public:
	class iterator {
	public:
		using iterator_catigory = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator(Node* p = nullptr) :ptr(p) {}

		pointer   operator->() { return &(ptr->data); }
		reference operator*() { return ptr->data ; }

		iterator& operator++()    { ptr=ptr->next; return *this; }
		iterator  operator++(int) { iterator tmp = *this; ptr = ptr->next; return tmp; }
		iterator& operator--()    { ptr = ptr->prev; return *this; }
		iterator  operator--(int) { iterator tmp = *this; ptr = ptr->prev; return tmp; }
		
		bool operator==(const iterator& other) { return other.ptr == ptr; }
		bool operator!=(const iterator& other) { return other.ptr != ptr; }
	private:
	   Node* ptr;
	   friend class my_list;
	};
	class const_iterator {
	public:
		using iterator_catigory = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		const_iterator(Node* p = nullptr) : ptr(p) {}
		const_iterator(const iterator& other) :ptr(other.ptr){}

		pointer   operator->()  const { return &(ptr->data); }
		reference operator*() const { return ptr->data; }

		const_iterator& operator++()    { ptr = ptr->next; return *this; }
		const_iterator  operator++(int) { const_iterator tmp = *this; ptr = ptr->next; return tmp; }
		const_iterator& operator--()    { ptr = ptr->prev; return *this; }
		const_iterator  operator--(int) { const_iterator tmp = *this; ptr = ptr->prev; return tmp; }

		bool operator==(const const_iterator& other) const { return other.ptr == ptr; }
		bool operator!=(const const_iterator& other) const { return other.ptr != ptr; }
	private:
		Node* ptr;
		friend class my_list;

	};

	class reverse_iterator {
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using pointer = T*;
		using reference = T&;
		using difference_type = std::ptrdiff_t;
		using value_type = T;

		reverse_iterator(Node* p = nullptr) :ptr(p) {}

		pointer operator->() { return &(ptr->data); }
		reference operator*() { return ptr->data; }

		reverse_iterator operator++() { ptr = ptr->prev; return *this; }
		reverse_iterator operator++(int) { reverse_iterator tmp = *this; ptr = ptr->prev; return tmp; }
		reverse_iterator operator--() { ptr = ptr->next; return*this; }
		reverse_iterator operator--(int) { reverse_iterator tmp = *this; ptr = ptr->next; return tmp; }

		bool operator==(const reverse_iterator& other) { return other.ptr == ptr; }
		bool operator!=(const reverse_iterator& other) { return other.ptr != ptr; }
	private:
		Node* ptr;
		friend class my_list;
	};

	class const_reverse_iterator {
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using pointer = const T*;
		using reference = const T&;
		using difference_type = std::ptrdiff_t;
		using value_type = T;

		const_reverse_iterator(Node* p = nullptr) :ptr(p) {}
		const_reverse_iterator(const reverse_iterator& other): ptr(other.ptr) {}

		pointer operator->() const { return &(ptr->data); }
		reference operator*() const { return (ptr->data); }

		const_reverse_iterator operator++() { ptr = ptr->prev; return *this; }
		const_reverse_iterator operator++(int) { const const_reverse_iterator tmp = *this; ptr = ptr->prev; return tmp; }
		const_reverse_iterator operator--() { ptr = ptr->next; return *this; }
		const_reverse_iterator operator--(int) { const const_reverse_iterator tmp = *this; ptr = ptr->next; return tmp; }

		bool operator==(const const_reverse_iterator& other) const { return other.ptr == ptr; }
		bool operator!=(const const_reverse_iterator& other) const { return other.ptr != ptr; }
	private:
		Node* ptr;
		friend class my_list;
	};
	// Constructor, destructor, and basic operations
	my_list();
	~my_list();
	my_list(const my_list& other);
	my_list& operator=(const my_list& other);
	void push_front(const T& value);
	void pop_front();
	iterator insert(iterator position, const T& value);
	iterator erase(iterator position);
	iterator erase(iterator rangeBegin, iterator rangeEnd);
	size_t get_size() const { return size; }
	bool empty() const { return size == 0; }

	iterator begin() { return iterator(head); }
	iterator end() { return iterator(nullptr); }
	const_iterator cbegin() const { return const_iterator(head); }
	const_iterator cend() const { return const_iterator(nullptr); }
	reverse_iterator rbegin() { return reverse_iterator(tail); }
	reverse_iterator rend() { return reverse_iterator(nullptr); }
	const_reverse_iterator crbegin() const { return const_reverse_iterator(tail); }
	const_reverse_iterator crend() const { return const_reverse_iterator(nullptr); }


};
