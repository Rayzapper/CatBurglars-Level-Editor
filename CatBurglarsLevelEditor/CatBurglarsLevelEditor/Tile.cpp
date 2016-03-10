#include "Tile.h"

static const int width = 64, height = 64;
static int selectedID = 0, currentLayer = 0;
static bool changeAllowed = true;
static sf::Texture *texture1, *texture2, *textureProps;
static sf::RenderWindow *window;
static TextureHandler *textureHandler;
static string *mapType;

Tile::Tile(sf::Vector2i position, int ID, TextureHandler *textures, int layer, string *type)
: Entity(position, sf::IntRect(position.x, position.y, width, height)), mTileID(ID), mLayer(layer)
{
	mapType = type;
	textureHandler = textures;
	texture1 = textureHandler->GetTexture(0);
	texture2 = textureHandler->GetTexture(20);
	textureProps = textureHandler->GetTexture(19);
	if (ID < 1000)
	{
		if (*mapType == "Prison1")
			mSprite.setTexture(*texture1, true);
		else if (*mapType == "Museum")
			mSprite.setTexture(*texture2, true);
		mSprite.setTextureRect(sf::IntRect((ID % 3) * width, floor(ID / 3) * height, width, height));
	}
	else
	{
		mSprite.setTexture(*textureProps, true);
		mSprite.setTextureRect(sf::IntRect(((ID - 1000) % 3) * width, floor((ID - 1000) / 3) * height, width, height));
	}
}

Tile::~Tile()
{

}

void Tile::Update(sf::Vector2i mousePosition)
{
	mMouse = mHitBox.contains(mousePosition);
	if (mMouse)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (changeAllowed && mLayer == currentLayer)
			{
				mTileID = selectedID;
				if (mTileID < 1000)
				{
					if (*mapType == "Prison1")
						mSprite.setTexture(*texture1, true);
					else if (*mapType == "Museum")
						mSprite.setTexture(*texture2, true);
					mSprite.setTextureRect(sf::IntRect((mTileID % 3) * width, floor(mTileID / 3) * height, width, height));
				}
				else
				{
					mSprite.setTexture(*textureProps, true);
					mSprite.setTextureRect(sf::IntRect(((mTileID - 1000) % 3) * width, floor((mTileID - 1000) / 3) * height, width, height));
				}
			}
			mClicked = true;
		}
		else
			mClicked = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			mRightClicked = true;
		else
			mRightClicked = false;
	}
	else
	{
		mClicked = false;
		mRightClicked = false;
	}
}

void Tile::Render(int alpha)
{
	mSprite.setColor(sf::Color(255, 255, 255, alpha));
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
}

void Tile::Initialize(sf::RenderWindow *mainWindow)
{
	window = mainWindow;
}

sf::Vector2i Tile::GetSize(){ return sf::Vector2i(width, height); }

void Tile::IDChangeInfo(int ID, bool allowed, int layer)
{
	selectedID = ID;
	changeAllowed = !allowed;
	if (layer == 2 || layer == 3 || layer == 5)
		changeAllowed = false;
	currentLayer = layer;
}

void Tile::SetID(int ID)
{
	mTileID = ID;
}

int Tile::GetID(){ return mTileID; }

bool Tile::GetMouseover(){ return mMouse; }

bool Tile::GetClicked(){ return mClicked; }

bool Tile::GetRightClicked() { return mRightClicked; }