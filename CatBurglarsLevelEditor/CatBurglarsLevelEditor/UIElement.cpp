#include "UIElement.h"

static sf::Texture *texture;
static sf::RenderWindow *window;
static TextureHandler *textureHandler;

UIElement::UIElement(sf::Vector2i position, int width, int height, int textureID, TextureHandler *textures)
: Entity(position, sf::IntRect(position.x, position.y, width, height))
{
	textureHandler = textures;
	texture = textureHandler->GetTexture(textureID);
	mSprite.setTexture(*texture, true);
	mSprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

UIElement::~UIElement()
{

}

void UIElement::Update(sf::Vector2i mousePosition)
{

}

void UIElement::Render()
{
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
}

void UIElement::Initialize(sf::RenderWindow *mainWindow)
{
	window = mainWindow;
}