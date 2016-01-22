#ifndef TILE_H
#define TILE_H

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile();
	~Tile();
	void Render();
};

#endif