#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "UIElement.h"
#include "Tile.h"

class Editor
{
public:
	Editor();
	~Editor();
	void Run();
private:
	void Initialize();
	void Update();
	void Render();
	typedef vector<Tile*> TileColumn;
	typedef vector<TileColumn> TileLayer;
	TileLayer mTileLayerBottom, mTileLayer2, mTileLayer3;
	int mSelectedLayer = 0, mCurrentMapSizeX, mCurrentMapSizeY;
};

#endif