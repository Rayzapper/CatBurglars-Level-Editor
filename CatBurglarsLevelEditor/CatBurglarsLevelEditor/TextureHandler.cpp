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
	mSelectorTexture.loadFromFile("Resources/Selector.png");
	mSaveTexture.loadFromFile("Resources/Save.png");
}

sf::Texture* TextureHandler::GetTexture(int ID)
{
	if (ID == 0)
		return &mTileTexture;
	if (ID == 1)
		return &mSidebarTexture;
	if (ID == 2)
		return &mSelectorTexture;
	if (ID == 3)
		return &mSaveTexture;
}