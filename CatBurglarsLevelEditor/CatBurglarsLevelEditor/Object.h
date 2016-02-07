#ifndef OBJECT_H
#define OBJECT_H

#include "Entity.h"

class Object : public Entity
{
public:
	Object(sf::Vector2i position, sf::IntRect rect, int layer, int ID, int textureID, TextureHandler *textures);
	~Object();
	void Update(sf::Vector2i mousePosition);
	void Render();
	static void Initialize(sf::RenderWindow *mainWindow, sf::Font *mainFont);
	sf::Vector2i GetMapPosition();
	void SetChannel(int number);
	int GetChannel();
	int GetID();
	int GetLayer();
private:
	int mObjectID, mChannel = -1, mLayer;
	sf::Vector2i mTilePosition;
};

#endif