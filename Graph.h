#pragma once
#include "CarAccident.h"
#include "County.h"
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<iterator>
#include "HashTable.h"
using namespace std;

class Graph
{
private:
    //ADJACENCY LIST
    map<string, vector<string>> graph;

public:
    //MODIFIERS
    void insertEdge(string from, vector<string> to);

    //CHECKERS
    bool isEdge(string from, string to);
    bool has(string s);
    
    //STATISTICS
    void printGraph();
    vector<string> connectingPath(string firstCounty, string secondCounty);
};



