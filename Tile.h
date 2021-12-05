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
	sf::Sprite finalPath;
	bool isPath;
	bool isCrossed;
	bool isFinalPath;

public:
	sf::Sprite path;
	sf::Sprite wall;
	Tile();
	void Draw(sf::RenderWindow& window);
	void makePath(bool yes);
	void makeCrossed(bool yes);
	void makeFinalPath(bool yes);
	void setSpritePositions();
	void setPosition(int x, int y);
};

