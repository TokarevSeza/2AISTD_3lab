#pragma once
#include <iostream>
using namespace std;
template <class K, class V>
class Elem
{
	Elem<K, V>* next;
	V data;
	K key;
	void set_next(Elem<K, V>* new_element) { next = new_element; }
	void set_data(V new_data) { data = new_data; }
	void set_key(K new_key) { key = new_key; }

public:
	Elem() { }
	Elem<K, V>* get_next() { return next; }
	V get_data() { return data; }
	K get_key() { return key; }
	~Elem() {}
	template <class K, class V> friend class Queue;
};