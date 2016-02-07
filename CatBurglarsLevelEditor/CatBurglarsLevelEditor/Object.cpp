#include "Object.h"

static const int width = 64, height = 64;
static sf::Texture *texture;
static sf::RenderWindow *window;
static sf::Font *font;
static TextureHandler *textureHandler;

Object::Object(sf::Vector2i position, sf::IntRect rect, int layer, int ID, int textureID, TextureHandler *textures)
: Entity(position, rect), mLayer(layer), mObjectID(ID), mTilePosition((position.x - 256) / width, position.y / height)
{
	textureHandler = textures;
	texture = textureHandler->GetTexture(textureID);
	mSprite.setTexture(*texture, true);
}

Object::~Object()
{

}

void Object::Update(sf::Vector2i mousePosition)
{

}

void Object::Render()
{
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
	if (mChannel >= 0)
	{
		sf::Text text;
		text.setColor(sf::Color::White);
		text.setFont(*font);
		text.setString(to_string(mChannel));
		text.setPosition(mPosition.x, mPosition.y);
		window->draw(text);
	}
}

void Object::Initialize(sf::RenderWindow *mainWindow, sf::Font *mainFont)
{
	font = mainFont;
	window = mainWindow;
}

sf::Vector2i Object::GetMapPosition()
{
	return mTilePosition;
}

void Object::SetChannel(int number)
{
	mChannel = number;
}

int Object::GetChannel(){ return mChannel; }

int Object::GetID(){ return mObjectID; }

int Object::GetLayer(){ return mLayer; }