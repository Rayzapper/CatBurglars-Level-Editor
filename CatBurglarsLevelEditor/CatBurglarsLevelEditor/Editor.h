#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Editor
{
public:
	Editor();
	~Editor();
	void Run();
private:
	sf::RenderWindow *mWindow;
	typedef vector<Tile*> TileColumn;
	typedef vector<TileColumn> TileArray;
	TileArray mTileArray;
};

#endif