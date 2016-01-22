#include "UIObject.h"

static sf::Texture texture;

UIObject::UIObject()
{

}

UIObject::~UIObject()
{

}

void UIObject::Render(sf::RenderWindow *window)
{
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
}

void UIObject::Initialize()
{
	if (!texture.loadFromFile("Resources/StartUI.png"))
	{
		//Error Code
	}
}