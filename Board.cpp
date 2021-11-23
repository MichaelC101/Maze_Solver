#include "Board.h"
#include "TextureManager.h"

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

void Board::leftClick(sf::Vector2i mousePos)
{

	auto BFSbuttonBounds = BFSbutton.getGlobalBounds();
	auto DjikstraButtonBounds = DjikstraButton.getGlobalBounds();
	auto resetButtonBounds = resetButton.getGlobalBounds();
	auto timeButtonBounds = timeButton.getGlobalBounds();

	if (resetButtonBounds.contains(mousePos.x, mousePos.y))
	{
		resetGame();
	}
	if (BFSbuttonBounds.contains(mousePos.x, mousePos.y))
	{
		//Start the BFS visualization
	}
	if (DjikstraButtonBounds.contains(mousePos.x, mousePos.y))
	{
		//Start the Djikstra visualization
	}
	if (timeButtonBounds.contains(mousePos.x, mousePos.y))
	{
		
	}
}


void Board::resetGame()
{
}


