#ifndef BUTTON_H
#define BUTTON_H

#include "Entity.h"

class Button : public Entity
{
public:
	Button(sf::Vector2i position, int width, int height, int textureID, TextureHandler *textures);
	~Button();
	void Update();
	void Render();
	static void Initialize(sf::RenderWindow *mainWindow);
};

#endif