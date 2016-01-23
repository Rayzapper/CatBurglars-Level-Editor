#include "TextureHandler.h"

TextureHandler::TextureHandler()
{

}

TextureHandler::~TextureHandler()
{

}

void TextureHandler::Initialize()
{
	mTileTexture.loadFromFile("Resources/TestTile.png");
	mSidebarTexture.loadFromFile("Resources/SideBar.png");
	mSelectorTexture.loadFromFile("Resources/SelectorBar.png");
}

sf::Texture* TextureHandler::GetTexture(int ID)
{
	if (ID == 0)
	{
		return &mTileTexture;
	}
	if (ID == 1)
	{
		return &mSidebarTexture;
	}
	if (ID == 2)
	{
		return &mSelectorTexture;
	}
}