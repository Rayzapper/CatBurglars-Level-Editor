#include "UIButton.h"

static sf::Texture texture;

UIButton::UIButton()
{

}

UIButton::~UIButton()
{

}

void UIButton::Render(sf::RenderWindow *window)
{

}

void UIButton::Initialize()
{
	if (!texture.loadFromFile("Resources/StartUI.png"))
	{
		//Error Code
	}
}