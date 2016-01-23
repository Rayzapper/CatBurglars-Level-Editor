#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Entity.h"

class UIElement : public Entity
{
public:
	UIElement(sf::Vector2i position);
	~UIElement();
	void Update();
	void Render();
	static void Initialize(sf::Texture *tex, sf::RenderWindow *mainWindow);
};

#endif