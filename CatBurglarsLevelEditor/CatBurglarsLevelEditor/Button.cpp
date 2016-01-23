#include "Button.h"

static sf::Texture *texture;

Button::Button()
{

}

Button::~Button()
{

}

void Button::Render(sf::RenderWindow *window)
{

}

void Button::Initialize(sf::Texture *tex)
{
	texture = tex;
}