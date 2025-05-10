#include "List_iterator.h"
#include <iostream>
#include <iterator>
#include <cstddef>

template <typename T>
 my_list<T>::my_list(): head(nullptr),tail(nullptr),size(0){}
 template <typename T>
 my_list<T>::~my_list() {
		while(head){
			Node* temp=head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		size = 0;
	}
template <typename T>
my_list<T>::my_list(const my_list& other):head(nullptr),tail(nullptr),size(0) {
	Node* current = other.head;
	while (current) {
		push_front(current->data);
		current = current->next;
	}
	my_list temp;
	while (head) {
		temp.push_front(head->data);
		pop_front();
	}
	*this = temp;
}

template <typename T>
my_list<T>&my_list<T>::operator=(const my_list& other) {
	if (this != &other) {
		my_list temp(other);
		Node *tempHead = head;
		Node *tempTail = tail;
		head = temp.head;
		tail = temp.tail;
		temp.head = tempHead;
		temp.tail = tempTail;
		size = temp.size;

	}
	return *this;
}

template <typename T>
void my_list<T>::push_front(const T& value) {
	Node* newNode = new Node(value);
	if (!head) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	size++;
}


template <typename T>
void my_list<T>::pop_front() {
	if (head) {
		Node* current = head;
		head = head->next;

		if (head) {
			head->prev = nullptr;
		}
		else {
			tail = nullptr;
		}
		delete current;
		size--;
	}
}


template <typename T>
typename my_list<T>::iterator my_list<T>::insert(iterator position, const T& value) {
	Node* newNode = new Node(value);
	if (!position.ptr) {
		if (tail) {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		else {
			head = tail = newNode;
		}

	}
	else if (position.ptr == head) {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	else {
			Node* current = position.ptr;
			newNode->next = current;
			newNode->prev = current->prev;
			current->prev->next = newNode;
			current->prev = newNode;

		}

	size++;
	return iterator(newNode);
}

template <typename T>
typename my_list<T>::iterator my_list<T>::erase(iterator position) {
	if (!position.ptr || !head) return end();
	Node* current = position.ptr;
	if (current == head) {
		head = current->next;
		if (head) {
			head->prev = nullptr;
		}
		else {
			tail = nullptr;
		}
	}
	else if (current == tail) {
		tail = current->prev;
		tail->next = nullptr;
	}else {
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	Node* next = current->next;
	delete current;
	size--;
	return iterator(next);
}

template <typename T>
typename my_list<T>::iterator my_list<T>::erase(iterator rangeBegin, iterator rangeEnd) {
	iterator current = rangeBegin;
	while (current != rangeEnd && current != end()) {
		current = erase(current);
	}
	return current;
}

// Explicit template instantiation (optional, for linking)
template class my_list<int>;
template class my_list<double>;
template class my_list<std::string>;

int main() {
	my_list<int> lst;
	lst.push_front(3);
	lst.push_front(2);
	lst.push_front(1);

	// Forward iteration
	for (auto it = lst.begin(); it != lst.end(); ++it) {
		std::cout << *it << " "; // Outputs: 1 2 3
	}
	std::cout << "\n";

	// Backward iteration
	for (auto it = lst.rbegin(); it != lst.rend(); ++it) {
		std::cout << *it << " "; // Outputs: 3 2 1
	}
	std::cout << "\n";

	//// Bidirectional traversal
	//auto it = lst.end();
	//--it; // Move to last element
	//std::cout << *it << "\n"; // Outputs: 3
	//--it;
	//std::cout << *it << "\n"; // Outputs: 2

	// Insert and erase
	lst.insert(lst.begin(), 0); // List: 0 1 2 3
	lst.erase(++lst.begin());   // List: 0 2 3
	for (const auto& x : lst) {
		std::cout << x << " "; // Outputs: 0 2 3
	}
	std::cout << "\n";

	return 0;
}