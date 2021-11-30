#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"



class Tile
{
	int xposition;
	int yposition;
	sf::Vector2i position;
	sf::Sprite crossed;
	bool isPath;
	bool isCrossed;

public:
	sf::Sprite path;
	sf::Sprite wall;
	Tile();
	void Draw(sf::RenderWindow& window);
	void makePath(bool yes);
	void makeCrossed(bool yes);
	void setSpritePositions();
	void setPosition(int x, int y);
};

