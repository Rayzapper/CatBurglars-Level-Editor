#ifndef BUTTON_H
#define BUTTON_H

#include "Entity.h"

class Button : public Entity
{
public:
	Button();
	~Button();
	void Render(sf::RenderWindow *window);
	static void Initialize();
private:
	sf::IntRect mHitBox;
};

#endif