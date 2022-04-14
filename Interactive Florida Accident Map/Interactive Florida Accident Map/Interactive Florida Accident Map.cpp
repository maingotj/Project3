#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "GraphicalInterface.h"
using namespace std;

int main()
{

    //READ IN DATA HERE
   /* string word, temp, line;

    fstream fileIn;
    fileIn.open("datatest.csv", ios::in);
    
    while (getline(fileIn, line))
    {
        stringstream s(line);

        while (getline(s, word, ','))
        {
            cout << word << endl;
        }
    }
    */
    GraphicalInterface graphics;

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "Florida Accident Road Map");

    int count = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close(); 
            if (event.type == sf::Event::KeyReleased)
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                cout << "click: " << ++count <<  ": " << position.x << " " << position.y << endl;
            }
        }
        window.clear(sf::Color(255, 255, 255));
        graphics.Draw(window);
        window.display();
    }

    TextureManager::Clear();a
    
    return 0;
};
