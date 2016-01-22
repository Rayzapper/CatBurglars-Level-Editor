#ifndef TILE_H
#define TILE_H

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile();
	~Tile();
	void Render();
	sf::Vector2i GetSize();
	void SetID(int ID);
	int GetID();
private:
	int mTileID = 0;
};

#endif