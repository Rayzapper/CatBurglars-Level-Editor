#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Entity.h"

class UIElement : public Entity
{
public:
	UIElement(sf::Vector2i position, int width, int height, int textureID, TextureHandler *textures);
	~UIElement();
	void Update();
	void Render();
	static void Initialize(sf::RenderWindow *mainWindow);
};

#endif