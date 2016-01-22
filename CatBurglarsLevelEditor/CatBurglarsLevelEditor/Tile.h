#ifndef TILE_H
#define TILE_H

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile();
	~Tile();
	void Render(sf::RenderWindow *window);
	static void Initialize();
	sf::Vector2i GetSize();
	void SetID(int ID);
	int GetID();
private:
	int mTileID = 0;
	sf::IntRect mHitBox;
};

#endif