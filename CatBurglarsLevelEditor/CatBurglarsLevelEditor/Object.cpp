#include "Object.h"

static const int width = 64, height = 64;
static sf::Texture *texture;
static sf::RenderWindow *window;
static sf::Font *font;
static TextureHandler *textureHandler;

Object::Object(sf::Vector2i position, sf::IntRect rect, int layer, int ID, int textureID, string script, string facing, int hold, TextureHandler *textures)
: Entity(position, rect), mLayer(layer), mObjectID(ID), mTilePosition((position.x - 256) / width, position.y / height), mScript(script), mFacing(facing), mHoldlength(hold)
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

void Object::Render(int alpha)
{
	mSprite.setColor(sf::Color(255, 255, 255, alpha));
	int left = 0, top = 0;
	if (mFacing == "S")
	{
		left = 0;
		top = 0;
	}
	else if (mFacing == "W")
	{
		left = 64;
		top = 0;
	}
	else if (mFacing == "E")
	{
		left = 0;
		top = 64;
	}
	else
	{
		left = 64;
		top = 64;
	}
	if (mFacing != "null")
		mSprite.setTextureRect(sf::IntRect(left, top, 64, 64));
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

void Object::SetChannel(int number)
{
	mChannel = number;
}

void Object::SetScript(string script)
{
	mScript = script;
}

void Object::SetFacing(string facing)
{
	mFacing = facing;
}

void Object::SetButtonHold(int hold)
{
	mHoldlength = hold;
}

void Object::SetRange(int range)
{
	mRange = range;
}

sf::Vector2i Object::GetMapPosition(){ return mTilePosition; }

int Object::GetChannel(){ return mChannel; }

int Object::GetID(){ return mObjectID; }

int Object::GetLayer(){ return mLayer; }

string Object::GetScript(){ return mScript; }

string Object::GetFacing(){ return mFacing; }

int Object::GetButtonHold(){ return mHoldlength; }

int Object::GetRange() { return mRange; }