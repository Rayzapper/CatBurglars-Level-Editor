#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "Entity.h"

class UIObject : public Entity
{
public:
	UIObject();
	~UIObject();
	void Render(sf::RenderWindow *window);
	static void Initialize();
};

#endif