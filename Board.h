#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Tile.h"
using namespace std;


class Board
{
	sf::Sprite timeButton;
	sf::Sprite BFSbutton;
	sf::Sprite DFSbutton;
	sf::Sprite DjikstraButton;
	sf::Sprite resetButton;
	sf::Sprite BellmanFordButton;
	vector<vector<Tile>> tiles;

public:
	Board();
	void Draw(sf::RenderWindow& window);
	void rightClick(sf::Vector2i mousePos);
	void leftClick(sf::Vector2i mousePos);
	void resetGame();
	void addTile(Tile& tile, int x, int y);
	void setMaze(vector<vector<bool>> matrix);
};

