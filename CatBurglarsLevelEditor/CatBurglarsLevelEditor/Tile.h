#ifndef TILE_H
#define TILE_H

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile(sf::Vector2i position, int ID);
	~Tile();
	void Render();
	static void Initialize(sf::Texture *tex, sf::RenderWindow *mainWindow);
	static sf::Vector2i GetSize();
	void SetID(int ID);
	int GetID();
private:
	int mTileID = 0;
	sf::IntRect mHitBox;
};

#endif