#include "HashTable.h"

//INITIALIZER
HashTable::HashTable()
{
    arr = new list<County*>[5];
    count = 0;
    capacity = 5;
    loadFactor = 0.8f;
}

//INSERT FUNCTIONS
void HashTable::insert(CarAccident* accident)
{
    int index = reducedHash(accident->getCounty());//get reduced hash using the county string

    bool found = false;
    for (auto member : arr[index]) //iterates through array of counties
    {
        if (member->getName() == accident->getCounty()) //checks if county already exists
        {
            member->insert(accident); //add accidents data to the county
            found = true;
        }
    }
    if (!found) //if county didn't already exist
    {
        count++;
        County* newCounty = new County(accident); //make a new county for it
        arr[index].push_back(newCounty); //add it to the county array
    }

    if (count / capacity >= loadFactor) //checks if load factor is to high
    {
        rehash();
    }
}
void HashTable::insert(County* county) //inserts a county instead of accident
{
    int index = reducedHash(county->getName());//get reduced hash using the county string
    arr[index].push_back(county);//add it to the county array
    count++;
}
int HashTable::reducedHash(string s)
{
    int prime = 7;
    int hash = 0;
    for (unsigned int i = 0; i < s.length(); i++) //loops through string
    {
        hash += s.at(i) * pow(7, i); //puts char value to the power of i and adds it to hash
        if (i == 8)
            break;
    }
    int reducedHash = hash % capacity;
    return reducedHash;
}
int HashTable::size() {//returns size
    return count;
}
void HashTable::rehash() {
    count = 0;
    capacity *= 2;
    list<County*>* temp = arr;//creat copy arr

    arr = new list<County*>[capacity]; //make arr a new county that fits

    for (int i = 0; i < capacity / 2; i++) //loops through to copy the old data into the new arr
    {
        if (temp[i].empty())
        {
            for (auto member : temp[i])
                insert(member);
        }

    }

    delete[] temp;
}

//CHECKERS
bool HashTable::has(string s)
{
    int index = reducedHash(s); //stores hash

    bool found = false;
    for (auto member : arr[index]) //iterates through arr
    {
        if (member->getName() == s) //checks if the names match
        {
            found = true;
        }
    }
    return found;
}
County* HashTable::getCounty(string s) {
    int index = reducedHash(s);
    for (auto member : arr[index]) //iterate through arr
    {
        if (member->getName() == s) //returns the county object if true
            return member;
    }
}

//STATISTICS
void HashTable::stats()
{
    for (int i = 0; i < capacity; i++) {
        for (auto member : arr[i])
        {
            member->setStats(); //sets stats of each county
        }
    }
}

