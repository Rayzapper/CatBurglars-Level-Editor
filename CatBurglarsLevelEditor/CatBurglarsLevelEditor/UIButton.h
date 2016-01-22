#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "UIObject.h"

class UIButton : public UIObject
{
public:
	UIButton();
	~UIButton();
	void Render(sf::RenderWindow *window);
	static void Initialize();
private:
	sf::IntRect mHitBox;
};

#endif