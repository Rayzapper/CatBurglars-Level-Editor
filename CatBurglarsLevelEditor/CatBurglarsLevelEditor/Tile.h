#ifndef TILE_H
#define TILE_H

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile(sf::Vector2i position, int ID, int textureID, TextureHandler *textures);
	~Tile();
	void Update(sf::Vector2i mousePosition);
	void Render();
	static void Initialize(sf::RenderWindow *mainWindow);
	static sf::Vector2i GetSize();
	static void SelectedID(int ID);
	void SetID(int ID);
	int GetID();
	bool GetMouseover();
private:
	int mTileID = 0;
};

#endif