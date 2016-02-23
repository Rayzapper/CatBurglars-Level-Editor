#include "TextureHandler.h"

static sf::Texture tileTexture, catTexture, selectorTexture, saveTexture, layerTexture, buttonTexture, crateTexture, deleteTexture, objectsTexture, doorTexture, guardTexture,
	tile2Texture, pageTexture, button2Texture, cameraTexture, computerTexture, door2Texture, crate2Texture, eventTexture;

TextureHandler::TextureHandler()
{

}

TextureHandler::~TextureHandler()
{

}

void TextureHandler::Initialize()
{
	tileTexture.loadFromFile("Resources/TileMap.png");
	tile2Texture.loadFromFile("Resources/Tilemap_3.png");
	catTexture.loadFromFile("Resources/cat.png");
	selectorTexture.loadFromFile("Resources/Selector.png");
	saveTexture.loadFromFile("Resources/Save.png");
	layerTexture.loadFromFile("Resources/LayerButtons.png");
	buttonTexture.loadFromFile("Resources/Button.png");
	crateTexture.loadFromFile("Resources/crate.png");
	deleteTexture.loadFromFile("Resources/Delete.png");
	doorTexture.loadFromFile("Resources/Door.png");
	guardTexture.loadFromFile("Resources/Guard.png");
	pageTexture.loadFromFile("Resources/PageButtons.png");
	button2Texture.loadFromFile("Resources/Button2.png");
	cameraTexture.loadFromFile("Resources/Camera.png");
	computerTexture.loadFromFile("Resources/Computer.png");
	door2Texture.loadFromFile("Resources/Door2.png");
	crate2Texture.loadFromFile("Resources/crate2.png");
	eventTexture.loadFromFile("Resources/Event.png");

	sf::Image deleteImage, catImage, buttonImage, crateImage, doorImage, guardImage, button2Image, cameraImage, computerImage, door2Image, crate2Image;

	deleteImage.loadFromFile("Resources/Delete.png");
	catImage.loadFromFile("Resources/cat.png");
	buttonImage.loadFromFile("Resources/Button.png");
	crateImage.loadFromFile("Resources/crate.png");
	doorImage.loadFromFile("Resources/Door.png");
	guardImage.loadFromFile("Resources/Guard.png");
	button2Image.loadFromFile("Resources/Button2.png");
	cameraImage.loadFromFile("Resources/CameraIcon.png");
	computerImage.loadFromFile("Resources/ComputerIcon.png");
	door2Image.loadFromFile("Resources/Door2Icon.png");
	crate2Image.loadFromFile("Resources/crate2.png");

	objectsTexture.create(192, 256);
	objectsTexture.update(deleteImage, 0, 0);
	objectsTexture.update(catImage, 64, 0);
	objectsTexture.update(buttonImage, 128, 0);
	objectsTexture.update(crateImage, 0, 64);
	objectsTexture.update(doorImage, 64, 64);
	objectsTexture.update(guardImage, 128, 64);
	objectsTexture.update(button2Image, 0, 128);
	objectsTexture.update(cameraImage, 64, 128);
	objectsTexture.update(computerImage, 128, 128);
	objectsTexture.update(door2Image, 0, 192);
	objectsTexture.update(crate2Image, 64, 192);
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
	else if (ID == 9)
		return &doorTexture;
	else if (ID == 10)
		return &guardTexture;
	else if (ID == 11)
		return &tile2Texture;
	else if (ID == 12)
		return &pageTexture;
	else if (ID == 13)
		return &button2Texture;
	else if (ID == 14)
		return &cameraTexture;
	else if (ID == 15)
		return &computerTexture;
	else if (ID == 16)
		return &door2Texture;
	else if (ID == 17)
		return &crate2Texture;
	else if (ID == 18)
		return &eventTexture;
	else
		return &deleteTexture;
}