#include "Board.h"
#include "TextureManager.h"
#include <thread>
#include <chrono>
#include <queue>
#include <stack>
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
		runDFS(window, adjList, src, end);
	}
	if (DjikstraButtonBounds.contains(mousePos.x, mousePos.y))
	{
		//Start the Djikstra visualization
		runDjikstra(window, adjList, src, end);
	}
	if (BellmanFordButtonBounds.contains(mousePos.x, mousePos.y))
	{
		//Start the Bellman-Ford visualization
		runBellmanFord(window, adjList, src, end);
	}

	if (timeButtonBounds.contains(mousePos.x, mousePos.y))
	{
		
	}
}

void Board::runBFS(sf::RenderWindow& window, vector<unordered_set<int>>& adjList, int src, int end)
{
	unordered_set<int> visited;
	queue<int> queue;
	vector<int> parents(end + 1, -1);
	visited.emplace(src);
	queue.push(src);
	vector<int> path;

	while (!queue.empty()) {
		int x = queue.front();
		if (x == end) {
			break;
		}

		//Code for visualizing the popped tile
		int front = queue.front();
		queue.pop();
		int yVal = front / 35 * 2 + 1;
		int xVal = front % 35 * 2 + 1;
		tiles[yVal][xVal].makeCrossed(true);
		Draw(window);
		window.display();
		//this_thread::sleep_for(std::chrono::milliseconds(1));


		vector<int> neighbors;
		for (auto it = adjList[x].begin(); it != adjList[x].end(); ++it) {
			neighbors.push_back(*it);
		}
		for (int v : neighbors) {
			if (visited.count(v) == 0) {
				visited.insert(v);
				queue.push(v);
				parents[v] = x;
			}
		}
	}
	//HIGHLIGHTING SELECTED PATH IN DARK GREEN
	int currNode = end;
	path.push_back(currNode);
	while (currNode != -1)
	{
		currNode = parents[currNode];
		path.push_back(currNode);
	}
	path.pop_back();
	for (int i : path)
	{
		int yVal = i / 35 * 2 + 1;
		int xVal = i % 35 * 2 + 1;
		tiles[yVal][xVal].makeFinalPath(true);
		tiles[yVal][xVal].makeCrossed(false);
		Draw(window);
		window.display();
	}
	cout << "Distance for BFS Path: " << path.size() << endl;
}

void Board::runDFS(sf::RenderWindow& window, vector<unordered_set<int>>& adjList, int src, int end)
{
	unordered_set<int> visited;
	stack<int> stack;
	vector<int> parents(end + 1, -1);
	visited.emplace(src);
	stack.push(src);
	vector<int> path;

	while (!stack.empty()) {
		int x = stack.top();
		if (x == end) {
			break;
		}


		//Code for visualizing the popped tile
		int front = stack.top();
		stack.pop();
		int yVal = front / 35 * 2 + 1;
		int xVal = front % 35 * 2 + 1;
		tiles[yVal][xVal].makeCrossed(true);
		Draw(window);
		window.display();
		//this_thread::sleep_for(std::chrono::milliseconds(1));

		vector<int> neighbors;
		for (auto it = adjList[x].begin(); it != adjList[x].end(); ++it) {
			neighbors.push_back(*it);
		}
		for (int v : neighbors) {
			if (visited.count(v) == 0) {
				visited.insert(v);
				stack.push(v);
				parents[v] = x;
			}
		}
	}
	//HIGHLIGHTING SELECTED PATH IN DARK GREEN
	int currNode = end;
	path.push_back(currNode);
	while (currNode != -1)
	{
		currNode = parents[currNode];
		path.push_back(currNode);
	}
	path.pop_back();
	for (int i : path)
	{
		int yVal = i / 35 * 2 + 1;
		int xVal = i % 35 * 2 + 1;
		tiles[yVal][xVal].makeFinalPath(true);
		tiles[yVal][xVal].makeCrossed(false);
		Draw(window);
		window.display();
	}
	cout << "Distance for DFS Path: " << path.size() << endl;
}

void Board::runDjikstra(sf::RenderWindow& window, vector<unordered_set<int>>& adjList, int src, int end)
{
	vector<int> path;
	unordered_set<int> computed;
	unordered_set<int> notComputed;
	computed.emplace(src);
	//filling notComputed with all verticies except src
	for (int i = 0; i < adjList.size(); i++) {
		if (computed.count(i) != 1) {
			notComputed.emplace(i);
		}
	}
	// distance to each verticy
	vector<int> d(adjList.size(), 99999);
	d[src] = 0;
	// keeps track of predecessor
	vector<int> p(adjList.size(), -1);

	for (auto it = adjList[src].begin(); it != adjList[src].end(); ++it) {
		d[*it] = 1;
		p[*it] = src;
	}
	tiles[1][1].makeCrossed(true);
	Draw(window);
	window.display();
	while (!notComputed.empty()) {
		//need the smallest index that hasnt been visited yet
		vector<int> temp = d;
		for (auto it = computed.begin(); it != computed.end(); ++it) {
			temp[*it] = 999999999;
		}

		int minIndex = std::min_element(temp.begin(), temp.end()) - temp.begin();
		computed.emplace(minIndex);

		//Trying to highlight what stuff has been done already
		int yVal = minIndex / 35 * 2 + 1;
		int xVal = minIndex % 35 * 2 + 1;
		tiles[yVal][xVal].makeCrossed(true);
		Draw(window);
		window.display();

		notComputed.erase(minIndex);

		for (auto it = adjList[minIndex].begin(); it != adjList[minIndex].end(); ++it) {
			if (notComputed.count(*it) != 0) {
				if (d[minIndex] + 1 < d[*it]) {
					d[*it] = d[minIndex] + 1;
					p[*it] = minIndex;
				}
			}
		}

	}

	//HIGHLIGHTING SELECTED PATH IN DARK GREEN
	int currNode = end;
	path.push_back(currNode);
	while (currNode != 0)
	{
		currNode = p[currNode];
		path.push_back(currNode);
	}
	for (int i : path)
	{
		int yVal = i / 35 * 2 + 1;
		int xVal = i % 35 * 2 + 1;
		tiles[yVal][xVal].makeFinalPath(true);
		tiles[yVal][xVal].makeCrossed(false);
		Draw(window);
		window.display();
	}
	cout << "Distance for Djikstra Path: " << path.size() << endl;
}

void Board::runBellmanFord(sf::RenderWindow& window, vector<unordered_set<int>>& adjList, int src, int end)
{
	vector<int> path;
	vector<int> d(adjList.size(), 9999999);
	vector<int> p(adjList.size(), -1);
	d[src] = 0;
	p[src] = 0;
	for (int j = 0; j < adjList.size() - 1; j++) {

		//Visualizing the nodes???? not sure micheal plz help
		//int yVal = j / 35 * 2 + 1;
		//int xVal = j % 35 * 2 + 1;
		//tiles[yVal][xVal].makeCrossed(true);
		//Draw(window);
		//window.display();

		for (int i = 0; i < adjList.size(); i++) {
			for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it) {
				if (d[*it] > d[i] + 1) {
					d[*it] = d[i] + 1;
					p[*it] = i;
				}
			}
		}
	}
	//HIGHLIGHTING SELECTED PATH IN DARK GREEN
	int currNode = end;
	path.push_back(currNode);
	while (currNode != 0)
	{
		currNode = p[currNode];
		path.push_back(currNode);
	}
	for (int i : path)
	{
		int yVal = i / 35 * 2 + 1;
		int xVal = i % 35 * 2 + 1;
		tiles[yVal][xVal].makeFinalPath(true);
		tiles[yVal][xVal].makeCrossed(false);
		Draw(window);
		window.display();
	}
	cout << "Distance for BellmanFord Path: " << path.size() << endl;
}

void Board::resetGame()
{
	for (int i = 0; i < 51; i++)
	{
		for (int j = 0; j < 71; j++)
		{
			tiles[i][j].makeCrossed(false);
			tiles[i][j].makeFinalPath(false);
		}
	}
}









