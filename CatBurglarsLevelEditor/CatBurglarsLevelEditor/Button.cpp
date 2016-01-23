#include "Button.h"

static sf::Texture *texture;
static sf::RenderWindow *window;

Button::Button(sf::Vector2i position, int width, int height)
: Entity(position), mHitBox(0, 0, width, height)
{

}

Button::~Button()
{

}

void Button::Render()
{

}

void Button::Initialize(sf::Texture *tex, sf::RenderWindow *mainWindow)
{
	window = mainWindow;
	texture = tex;
}