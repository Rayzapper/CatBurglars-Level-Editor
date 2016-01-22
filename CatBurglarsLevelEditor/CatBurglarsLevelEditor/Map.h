#ifndef MAP_H
#define MAP_H

#include "Tile.h"

class Map
{
public:
	Map();
	~Map();
	void Update();
	void Render();
private:
	typedef vector<Tile*> TileColumn;
	typedef vector<TileColumn> TileLayer;
	TileLayer mTileLayerBottom, mTileLayer2, mTileLayer3;
	int mSelectedLayer = 0, mMapSizeX, mMapSizeY;
};

#endif