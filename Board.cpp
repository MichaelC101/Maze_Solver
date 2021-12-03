#include "Board.h"
#include "TextureManager.h"
#include <thread>
#include <chrono>
#include <queue>
using namespace std;

Board::Board()
{
	BFSbutton.setTexture(TextureManager::getTexture("BFS"));
	BFSbutton.setPosition(0, 601);
	DFSbutton.setTexture(TextureManager::getTexture("DFS"));
	DFSbutton.setPosition(217, 601);
	DjikstraButton.setTexture(TextureManager::getTexture("Djikstra"));
	DjikstraButton.setPosition(651, 601);
	resetButton.setTexture(TextureManager::getTexture("reset"));
	resetButton.setPosition(921, 0);
	BellmanFordButton.setTexture(TextureManager::getTexture("BellmanFord"));
	BellmanFordButton.setPosition(868, 601);
	//mazeWall.setPosition(290, 50);
	timeButton.setTexture(TextureManager::getTexture("timingComparison"));
	timeButton.setPosition(434, 601);
	tiles.resize(51);
	for (int i = 0; i < 51; i++) //im dumb and cant figure out a better way of doing this
		tiles[i].resize(71);
}

void Board::Draw(sf::RenderWindow& window)
{
	window.draw(BFSbutton);
	window.draw(DjikstraButton);
	window.draw(resetButton);
	window.draw(timeButton);
	window.draw(DFSbutton);
	window.draw(BellmanFordButton);
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
			tiles[i][j].Draw(window);
	}
}

void Board::reDraw(sf::RenderWindow& window, int x, int y)
{
	tiles[y][x].Draw(window);
	tiles[y + 1][x].Draw(window);
	tiles[y - 1][x].Draw(window);
	tiles[y][x + 1].Draw(window);
	tiles[y][x - 1].Draw(window);
}

void Board::setMaze(vector<vector<bool>> matrix)
{
	//We need to iterate through every node and change what is is, wall v path v crossed
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j])
				tiles[i][j].makePath(true);
		}
	}
}

void Board::rightClick(sf::Vector2i mousePos)
{
	
}

void Board::addTile(Tile& tile, int y , int x)
{
	tiles[x][y] = tile;
}

void Board::leftClick(sf::Vector2i mousePos, sf::RenderWindow& window, vector<unordered_set<int>>& adjList, int src, int end)
{

	auto BFSbuttonBounds = BFSbutton.getGlobalBounds();
	auto DFSbuttonBounds = DFSbutton.getGlobalBounds();
	auto DjikstraButtonBounds = DjikstraButton.getGlobalBounds();
	auto BellmanFordButtonBounds = BellmanFordButton.getGlobalBounds();
	auto resetButtonBounds = resetButton.getGlobalBounds();
	auto timeButtonBounds = timeButton.getGlobalBounds();

	if (resetButtonBounds.contains(mousePos.x, mousePos.y))
	{
		resetGame();
	}
	if (BFSbuttonBounds.contains(mousePos.x, mousePos.y))
	{
		//Start the BFS visualization
		runBFS(window, adjList, src, end);
	}
	if (DFSbuttonBounds.contains(mousePos.x, mousePos.y))
	{
		//Start the DFS visualization
	}
	if (DjikstraButtonBounds.contains(mousePos.x, mousePos.y))
	{
		//Start the Djikstra visualization
	}
	if (BellmanFordButtonBounds.contains(mousePos.x, mousePos.y))
	{
		//Start the Bellman-Ford visualization
	}

	if (timeButtonBounds.contains(mousePos.x, mousePos.y))
	{
		
	}
}

void Board::runBFS(sf::RenderWindow& window, vector<unordered_set<int>>& adjList, int src, int end)
{
	auto start = chrono::high_resolution_clock::now();
	unordered_set<int> visited;
	queue<int> queue;
	visited.emplace(src);
	queue.push(src);
	vector<int> path;

	while (!queue.empty()) {
		int x = queue.front();
		if (x == end) {
			break;
		}
		path.push_back(x);

		//Code for visualizing the popped tile
		int front = queue.front();
		queue.pop();
		int yVal = front / 35 * 2 + 1;
		int xVal = front % 35 * 2 + 1;
		tiles[yVal][xVal].makeCrossed(true);
		Draw(window);
		window.display();
		this_thread::sleep_for(std::chrono::milliseconds(20));


		vector<int> neighbors;
		for (auto it = adjList[x].begin(); it != adjList[x].end(); ++it) {
			neighbors.push_back(*it);
		}
		for (int v : neighbors) {
			if (visited.count(v) == 0) {
				visited.insert(v);
				queue.push(v);
			}
		}
	}
}



void Board::resetGame()
{
	for (int i = 0; i < 51; i++)
	{
		for (int j = 0; j < 71; j++)
			tiles[i][j].makeCrossed(false);
	}
}









