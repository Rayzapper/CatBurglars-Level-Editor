#ifndef BUTTON_H
#define BUTTON_H

#include "Entity.h"

class Button : public Entity
{
public:
	Button(sf::Vector2i position, int width, int height, int textureID);
	~Button();
	void Update(sf::Vector2i mousePosition);
	void Render();
	bool GetMouseover();
	bool GetPressed();
private:
	bool mPressed = false;
};

#endif