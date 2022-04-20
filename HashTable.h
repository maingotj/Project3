#pragma once
#include "County.h"
#include "CarAccident.h"
#include <list>
#include <math.h>
#include <iostream>

class HashTable
{
private:
    int count;
    int capacity;
    float loadFactor;
    list<County*>* arr;
public:
    //INITIALIZER
    HashTable();

    //INSERT FUNCTIONS
    void insert(CarAccident* accident);
    void insert(County* county);
    int reducedHash(string s);
    int size();
    void rehash();
    
    //CHECKERS
    bool has(string s);
    County* getCounty(string s);
    
    //STATISTICS
    void stats();
};
