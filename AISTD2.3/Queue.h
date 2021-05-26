#pragma once
#include "Elem.h"
template <class K, class V>
class Queue
{
private:
	Elem<K, V>* head; // old elem
	Elem<K, V>* tail; // new elem
	void set_head(Elem<K, V>* key) { head = key; }
	void set_tail(Elem<K, V>* key) { tail = key; }
public:
	Queue()
	{
		head = nullptr;
		tail = nullptr;
	}
	bool is_empty()
	{
		if (tail == nullptr)
			return true;
		return false;
	}
	size_t get_size() // return a number of elements in queue
	{
		if (is_empty())
			return 0;
		int size = 1;
		for (Elem<K, V>* now = tail; now->get_next() != nullptr; now = now->get_next())
			size++;
		return size;
	}
	Elem<K, V>* top() // to know who will leave first
	{
		return head;
	}

	Elem<K, V>* push(V data) // adds to the end
	{
		Elem<K, V>* new_elem = new Elem<K, V>;
		new_elem->set_data(data);
		new_elem->set_key(get_size()); // key = index in array
		if (is_empty()) {
			head = new_elem;
			tail = new_elem;
		}
		else
		{
			new_elem->set_next(tail);
			tail = new_elem;
		}
		return new_elem;
	}

	Elem<K, V>* pop() {
		Elem<K, V>* to_delete;
		if (is_empty())
			throw out_of_range("the queue is empty");
		else if (get_size() == 1)
		{
			to_delete = head;
			head = tail = nullptr;
		}
		else
		{
			to_delete = head;
			for (Elem<K, V>* now = tail; now->get_next() != nullptr; now = now->get_next())
				head = now;
			head->next = nullptr;
		}
		return to_delete;
	}

	K search_key(V value) {
		Elem<K, V>* current = tail;
		while (current != nullptr)
		{
			if (current->get_data() == value)
				return current->get_key();
			current = current->get_next();
		}
		return -1;
	}

	~Queue() { while (!is_empty())	pop(); }
};