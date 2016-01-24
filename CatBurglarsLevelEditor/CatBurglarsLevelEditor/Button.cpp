#include "Button.h"

Button::Button(sf::Vector2i position, int width, int height, int textureID)
: Entity(position, sf::IntRect(position.x, position.y, width, height))
{
	
}

Button::~Button()
{

}

void Button::Update(sf::Vector2i mousePosition)
{
	mMouse = mHitBox.contains(mousePosition);
	if (mMouse)
	{
		mPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}
	else
		mPressed = false;
}

void Button::Render()
{
	
}

bool Button::GetMouseover(){ return mMouse; }

bool Button::GetPressed(){ return mPressed; }