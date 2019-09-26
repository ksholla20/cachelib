#pragma once

template <typename T>
struct ListNode {
public:
	ListNode<T>* prev;
	ListNode<T>* next;
	T val;
	ListNode(T t) : val(t), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList
{
private:
	ListNode<T> * beg = nullptr;
	ListNode<T> * end = nullptr;
public:
	DoublyLinkedList() {}
	void deleteNode(ListNode<T> * node) {
		if (node->prev) node->prev->next = node->next;
		if (node->next) node->next->prev = node->prev;
		if (node == beg) beg = node->next;
		if (node == end) end = node->prev;
		delete node;
	}

	ListNode<T>* addNode(T t) {
		ListNode<T> * node = new ListNode<T>(t);
		if (end) {
			end->next = node;
			node->prev = end;
			end = node;
		}
		else {
			beg = end = node;
		}
		return node;
	}

	void push_back(ListNode<T> * node) {
		if (node == end) return;
		if (node == beg) beg = beg->next;
		if (node->prev) node->prev->next = node->next;
		node->next->prev = node->prev;
		end->next = node;
		node->prev = end;
		node->next = nullptr;
		end = node;
	}

	void pop_front() {
		if (beg->next) beg->next->prev = beg->prev;
		if (beg == end) end = nullptr;
		auto tmp = beg;
		beg = beg->next;
		delete tmp;
	}

	ListNode<T>* get_front() {
		return beg;
	}

	bool hasNode() {
		return (beg != nullptr);
	}

	void clear() {
		while (beg) {
			auto tmp = beg;
			beg = beg->next;
			delete tmp;
		}
		beg = end = nullptr;
	}

	~DoublyLinkedList() {}
};

