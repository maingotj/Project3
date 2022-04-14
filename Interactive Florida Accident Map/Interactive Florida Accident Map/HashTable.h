#pragma once
#include "County.h"
#include <list>

class HashTable
{
	//This will have our hash functions and the other things for the hash table

private:
	int count;
	int capacity;
	float loadFactor;
	list<County> *arr;

public:
	HashTable() {
		arr = new list<County>[10];
		count = 0;
		capacity = 10;
		loadFactor = 0.75f;
	}

	void insert() {}
	bool has() {}
	int size() {
		return count;
	}
	void rehash(){}
};

