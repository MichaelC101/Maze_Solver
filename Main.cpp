#include "Board.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;

// Helper function prototypes
vector<unordered_set<int>> generateGraph(int H, int W);
vector<vector<bool>> graphToMaze(vector<unordered_set<int>>& adjList, int H, int W);
void printMaze(vector<vector<bool>>& matrix);
void printList(vector<unordered_set<int>>& adjList);

// Program Driver
int main()
{
	// 2500 x 40 gives 100k vertices and fits in console
	// const int Y = 2500, X = 40;
	//auto bigAdjList = generateGraph(Y, X);
	//auto bigMatrix = graphToMaze(bigAdjList, Y, X);
	//printMaze(bigMatrix);

	// Seed the randomizer
	srand(time(0));

	//SFML START
	Board board;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Maze Runner");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					board.leftClick(sf::Mouse::getPosition(window), window);
				}
			}
		}
		window.clear(sf::Color(173, 216, 230, 255));
		board.Draw(window);
		window.display();
	}
	TextureManager::Clear();
	return 0;
}

void printList(vector<unordered_set<int>>& adjList)
{
	for (unsigned int i = 0; i < adjList.size(); i++)
	{
		if (!adjList[i].empty())
		{
			cout << i << " -> ";
			for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it)
			{
				cout << *it << " ";
			}
			cout << endl;
		}
	}
}

