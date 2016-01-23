#include "Button.h"

static sf::Texture texture;

Button::Button()
{

}

Button::~Button()
{

}

void Button::Render(sf::RenderWindow *window)
{

}

void Button::Initialize()
{
	if (!texture.loadFromFile("Resources/StartUI.png"))
	{
		//Error Code
	}
}