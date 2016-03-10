#ifndef TILE_H
#define TILE_H

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile(sf::Vector2i position, int ID, TextureHandler *textures, int layer, string *type);
	~Tile();
	void Update(sf::Vector2i mousePosition);
	void Render(int alpha);
	static void Initialize(sf::RenderWindow *mainWindow);
	static sf::Vector2i GetSize();
	static void IDChangeInfo(int ID, bool allowed, int layer);
	void SetID(int ID);
	int GetID();
	bool GetMouseover();
	bool GetClicked();
	bool GetRightClicked();
private:
	int mTileID = 0, mLayer;
	bool mClicked, mRightClicked;
};

#endif