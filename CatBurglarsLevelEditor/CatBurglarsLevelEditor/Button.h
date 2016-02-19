#ifndef BUTTON_H
#define BUTTON_H

#include "Entity.h"

class Button : public Entity
{
public:
	Button(sf::Vector2i position, int width, int height);
	~Button();
	void Update(sf::Vector2i mousePosition);
	void Render(int alpha);
	bool GetMouseover();
	bool GetPressed();
	void SetActive(bool state);
	bool GetActive();
private:
	bool mPressed = false, mActive = true;
};

#endif