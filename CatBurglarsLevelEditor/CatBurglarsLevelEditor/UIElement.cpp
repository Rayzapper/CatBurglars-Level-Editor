#include "UIElement.h"

static sf::Texture *texture;
static sf::RenderWindow *window;

UIElement::UIElement(sf::Vector2i position)
: Entity(position)
{

}

UIElement::~UIElement()
{

}

void UIElement::Render()
{
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
}

void UIElement::Initialize(sf::Texture *tex, sf::RenderWindow *mainWindow)
{
	window = mainWindow;
	texture = tex;
}