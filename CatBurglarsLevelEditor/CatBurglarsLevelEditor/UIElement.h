#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Entity.h"

class UIElement : public Entity
{
public:
	UIElement();
	~UIElement();
	void Render(sf::RenderWindow *window);
	static void Initialize(sf::Texture *tex);
};

#endif