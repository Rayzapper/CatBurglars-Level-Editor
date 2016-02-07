#include "TextureHandler.h"

static sf::Texture tileTexture, catTexture, selectorTexture, saveTexture, layerTexture, buttonTexture, crateTexture, deleteTexture, objectsTexture;

TextureHandler::TextureHandler()
{

}

TextureHandler::~TextureHandler()
{

}

void TextureHandler::Initialize()
{
	tileTexture.loadFromFile("Resources/TileMap.png");
	catTexture.loadFromFile("Resources/cat.png");
	selectorTexture.loadFromFile("Resources/Selector.png");
	saveTexture.loadFromFile("Resources/Save.png");
	layerTexture.loadFromFile("Resources/LayerButtons.png");
	buttonTexture.loadFromFile("Resources/Button.png");
	crateTexture.loadFromFile("Resources/crate.png");
	deleteTexture.loadFromFile("Resources/Delete.png");

	sf::Image deleteImage, catImage, buttonImage, crateImage;

	deleteImage.loadFromFile("Resources/Delete.png");
	catImage.loadFromFile("Resources/cat.png");
	buttonImage.loadFromFile("Resources/Button.png");
	crateImage.loadFromFile("Resources/crate.png");

	objectsTexture.create(192, 128);
	objectsTexture.update(deleteImage, 0, 0);
	objectsTexture.update(catImage, 64, 0);
	objectsTexture.update(buttonImage, 128, 0);
	objectsTexture.update(crateImage, 0, 64);
}

sf::Texture* TextureHandler::GetTexture(int ID)
{
	if (ID == 0)
		return &tileTexture;
	else if (ID == 1)
		return &catTexture;
	else if (ID == 2)
		return &selectorTexture;
	else if (ID == 3)
		return &saveTexture;
	else if (ID == 4)
		return &layerTexture;
	else if (ID == 5)
		return &buttonTexture;
	else if (ID == 6)
		return &crateTexture;
	else if (ID == 7)
		return &deleteTexture;
	else if (ID == 8)
		return &objectsTexture;
	else
		return &deleteTexture;
}