#include "UIElement.h"

static sf::Texture *texture;
static sf::RenderWindow *window;

UIElement::UIElement(sf::Vector2i position)
: Entity(position)
{
	mSprite.setTexture(*texture, true);
	mSprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
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