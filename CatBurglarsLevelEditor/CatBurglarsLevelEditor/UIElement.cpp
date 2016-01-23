#include "UIElement.h"

static sf::Texture *texture;

UIElement::UIElement()
{

}

UIElement::~UIElement()
{

}

void UIElement::Render(sf::RenderWindow *window)
{
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
}

void UIElement::Initialize(sf::Texture *tex)
{
	texture = tex;
}