#ifndef OBJECT_H
#define OBJECT_H

#include "Entity.h"

class Object : public Entity
{
public:
	Object(sf::Vector2i position, sf::IntRect rect, int layer, int ID, int textureID, string script, string facing, int hold, TextureHandler *textures);
	~Object();
	void Update(sf::Vector2i mousePosition);
	void Render();
	static void Initialize(sf::RenderWindow *mainWindow, sf::Font *mainFont);
	void SetChannel(int number);
	void SetScript(string script);
	void SetFacing(string facing);
	void SetButtonHold(int hold);
	void SetRange(int range);
	sf::Vector2i GetMapPosition();
	int GetChannel();
	int GetID();
	int GetLayer();
	string GetScript();
	string GetFacing();
	int GetButtonHold();
	int GetRange();
private:
	int mObjectID, mChannel = -1, mLayer, mHoldlength = -1, mRange = -1;
	string mScript, mFacing;
	sf::Vector2i mTilePosition;
};

#endif