#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "GraphicalInterface.h"
#include "Graph.h"
#include "HashTable.h"
#include "CarAccident.h"
using namespace std;

//THESE FUNCTIONS READ IN THE DATA FOR THE DATA STRUCTURES
void readAccidents(string file, HashTable& hashTable) {
    string processedWord, temp1, temp2, line;
    ifstream fileIn;
    fileIn.open(file, ios::in);

    float x, y;
    string county;
    int weekday;
    int speedLimit;
    bool injury;
    bool death;
    bool impairedDriver;
    getline(fileIn, line);
    while (getline(fileIn, line)) //iterate through whole file.
    {
        stringstream s(line);

        getline(s, processedWord, ','); //stops at , as the file is a csv
        x = stof(processedWord); //stores data from csv

        getline(s, processedWord, ',');
        y = stof(processedWord);

        getline(s, processedWord, ',');
        county = processedWord;

        getline(s, processedWord, ',');
        weekday = stoi(processedWord);

        getline(s, processedWord, ',');
        if (processedWord != "") //checks if value exists
            speedLimit = stoi(processedWord);
        else
            speedLimit = 0; //if not make it zero

        getline(s, processedWord, ',');
        getline(s, temp1, ',');
        getline(s, temp2, ',');
        injury = stoi(processedWord) + stoi(temp2); //adds injuries and serious injuries together
        death = stoi(temp1); //store as int

        getline(s, processedWord, ',');
        if (processedWord == "N") //initialize bool values
            impairedDriver = false;
        else
            impairedDriver = true;


        //make accident object with data.
        CarAccident* addedAccident = new CarAccident(x, y, county, weekday, speedLimit, injury, death, impairedDriver);

        hashTable.insert(addedAccident); //insert accident into hashtable
    }
    fileIn.close(); //close the file
}
void initGraph(string file, Graph& graph) {
    ifstream fileIn;
    fileIn.open(file, ios::in);

    string from, to, line;
    vector<string> vecTo;
    getline(fileIn, line);
    while (getline(fileIn, line))
    {
        stringstream s(line);
        getline(s, from, ',');
        while (getline(s, to, ','))
        {
            vecTo.push_back(to);
        }
        graph.insertEdge(from, vecTo);

        vecTo.clear();
    }
}

int main()
{
    //INITIALIZE THE DATA STRUCTURES
    HashTable hashTable;
    Graph graph;

    //files to be read.
    readAccidents("Crashes_All_0.csv", hashTable);
    readAccidents("Crashes_All_1.csv", hashTable);
    readAccidents("Crashes_All_2.csv", hashTable);
    readAccidents("Crashes_All_3.csv", hashTable);
    initGraph("AdjacencyList.csv", graph);
    
    //INITIALIZE THE STATS THAT WILL BE DISPLAYED
    hashTable.stats();
    
    //THIS IS OUR OBJECT THAT HANDLES ALL THE GRAPHICS
    GraphicalInterface graphics(hashTable, graph);

    //WHILE LOOP FOR WINDOW
    sf::RenderWindow window(sf::VideoMode(1500, 1100), "Florida County Crash Map");
    while (window.isOpen())
    {
        graphics.checkEvent(window);
        window.clear(sf::Color(255, 255, 255));
        graphics.Draw(window);
        window.display();
    }

    TextureManager::Clear();
    return 0;
};

