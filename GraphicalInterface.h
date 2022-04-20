#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <map>
#include <iostream>
#include <string>
#include "Graph.h"
#include "HashTable.h"

using namespace std;

class GraphicalInterface
{

private:
    //SPRITES
    map<string, sf::Sprite> sprites;  //maps user input string to a sprite at that location on the map
    sf::Sprite floridaMap;
    sf::Sprite Escambia, SantaRosa, Okaloosa, Walton, Holmes,
            Washington, Bay, Jackson, Calhoun, Gulf, Gadsden, Liberty,
            Franklin, Leon, Wakulla, Jefferson, Madison, Taylor, Hamilton,
            Suwannee, Lafayette, Dixie, Gilchrist, Alachua, Columbia, Baker,
            Union, Bradford, Nassau, Duval, Clay, StJohns, Putnam, Flagler,
            Levy, Marion, Volusia, Citrus, Sumter, Lake, Seminole, Orange,
            Hernando, Pasco, Pinellas, Hillsborough, Polk, Osceola, Brevard,
            Manatee, Hardee, Highlands, Okeechobee, IndianRiver, StLucie, Martin,
            Sarasota, Desoto, Glades, Charlotte, Lee, Hendry, PalmBeach, Collier,
            Broward, Monroe, MiamiDade;

    //USER INPUT TEXTBOX OBJECTS
    sf::RectangleShape textBox;
    bool on = true;
    bool capital = false, secondCounty = false, drawCountybool = false;
    int flash = 0;                                   //used to flash the user input cursor every 800 frames
    sf::Vector2<float> vector;                       //position vector reused to set object positions
    map<int, char> keyCodes;                         //maps the event.key.code of user input to
    //corresponding char

    //SFML TEXT OBJECTS
    sf::Font georgia;
    sf::Text search, cursor, label_county, label_speed, label_deaths, label_injuries, label_impairments, label_weekend, label_weekday, label_county2, label_graphTime, label_hashTime;
    sf::Text countyName, county, speed, deaths, injuries, impairments, weekend, weekday, path_fatal, path_injury, path_crashes, fatal, injure, crashes;

    //MISC SFML
    sf::Color color;
    sf::VertexArray line;
    std::vector<string> countiesDisplay, path, pathData;

    //TIMING NUMBERS
    long numCalculations = 0;
    long totalSecondsHash = 0;
    long totalSecondsGraph = 0;
    long avgTimeHash;
    long avgTimeGraph;

    //DATA STRUCTURES
    Graph* myGraph;
    HashTable* myHashTable;

public:
    //CONSTRUCTOR
    GraphicalInterface(HashTable& hashtable, Graph& graph);
    void setSprites();

    //DRAWING FUNCTIONS
    void Draw(sf::RenderWindow& window);
    void drawSelectedCounties(sf::RenderWindow& window);
    void drawCountyStats(sf::RenderWindow& window);
    void flashCursor();
    void moveCursor();

    //EVENT HANDLERS
    void checkEvent(sf::RenderWindow& window);
    void handleCountyInput(string input);
    void timeInput(string s);
};




