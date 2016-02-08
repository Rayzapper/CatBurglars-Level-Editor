#include "Button.h"

Button::Button(sf::Vector2i position, int width, int height)
: Entity(position, sf::IntRect(position.x, position.y, width, height))
{
	
}

Button::~Button()
{
	
}

void Button::Update(sf::Vector2i mousePosition)
{
	mHitBox.left = mPosition.x;
	mHitBox.top = mPosition.y;
	mMouse = mHitBox.contains(mousePosition);
	if (mMouse && mActive)
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

void Button::SetActive(bool state)
{
	mActive = state;
}

bool Button::GetActive(){ return mActive; }