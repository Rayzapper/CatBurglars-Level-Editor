#include "Button.h"

static sf::Texture *texture;
static sf::RenderWindow *window;
static TextureHandler *textureHandler;

Button::Button(sf::Vector2i position, int width, int height, int textureID, TextureHandler *textures)
: Entity(position, sf::IntRect(position.x, position.y, width, height))
{
	textureHandler = textures;
	texture = textureHandler->GetTexture(textureID);
	mSprite.setTexture(*texture, true);
}

Button::~Button()
{

}

void Button::Update(sf::Vector2i mousePosition)
{

}

void Button::Render()
{

}

void Button::Initialize(sf::RenderWindow *mainWindow)
{
	window = mainWindow;
}