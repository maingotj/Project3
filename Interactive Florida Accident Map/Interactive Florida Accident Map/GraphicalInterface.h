#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <map>
using namespace std;

class GraphicalInterface
{
	map<string, pair<int, int>> locations;
	sf::Sprite floridaMap;

public:
	GraphicalInterface()
	{
		floridaMap.setPosition(200, 20);
		floridaMap.setTexture(TextureManager::GetTexture("florida"));


	}
	void Draw(sf::RenderWindow& window)
	{
		window.draw(floridaMap);
	}
};

