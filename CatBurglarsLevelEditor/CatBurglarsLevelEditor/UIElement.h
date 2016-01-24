#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Entity.h"

class UIElement : public Entity
{
public:
	UIElement(sf::Vector2i position, int hitboxWidth, int hitboxHeight, int textureID, TextureHandler *textures);
	~UIElement();
	void Update(sf::Vector2i mousePosition);
	void Render();
	static void Initialize(sf::RenderWindow *mainWindow);
	bool GetMouseover();
};

#endif