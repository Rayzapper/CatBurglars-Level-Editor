#include "UIElement.h"

static sf::Texture *texture;
static sf::RenderWindow *window;
static TextureHandler *textureHandler;

UIElement::UIElement(sf::Vector2i position, int hitboxWidth, int hitboxHeight, int textureID, TextureHandler *textures)
: Entity(position, sf::IntRect(position.x, position.y, hitboxWidth, hitboxHeight))
{
	textureHandler = textures;
	texture = textureHandler->GetTexture(textureID);
	mSprite.setTexture(*texture, true);
	mSprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	mHitBox.left -= position.x;
	mHitBox.top -= position.y;
}

UIElement::~UIElement()
{

}

void UIElement::Update(sf::Vector2i mousePosition)
{
	mMouse = mHitBox.contains(mousePosition);
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

bool UIElement::GetMouseover(){ return mMouse; }