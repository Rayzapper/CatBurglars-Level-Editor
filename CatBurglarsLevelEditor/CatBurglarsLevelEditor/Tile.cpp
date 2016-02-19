#include "Tile.h"

static const int width = 64, height = 64;
static int selectedID = 0, currentLayer = 0, currentPage = 0;
static bool changeAllowed = true;
static sf::Texture *texture1, *texture2;
static sf::RenderWindow *window;
static TextureHandler *textureHandler;

Tile::Tile(sf::Vector2i position, int ID, TextureHandler *textures, int layer, int page)
: Entity(position, sf::IntRect(position.x, position.y, width, height)), mTileID(ID), mLayer(layer)
{
	textureHandler = textures;
	texture1 = textureHandler->GetTexture(0);
	texture2 = textureHandler->GetTexture(11);
	currentPage = page;
	mSprite.setTexture(*texture1, true);
	mSprite.setTextureRect(sf::IntRect((ID % 3) * width, floor(ID / 3) * height, width, height));
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
				if (currentPage == 0)
					mSprite.setTexture(*texture1, true);
				else if (currentPage == 1)
					mSprite.setTexture(*texture2, true);
				mSprite.setTextureRect(sf::IntRect((mTileID % 3) * width, floor(mTileID / 3) * height, width, height));
			}
			mClicked = true;
		}
		else
			mClicked = false;
	}
	else
		mClicked = false;
}

void Tile::Render()
{
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
}

void Tile::Initialize(sf::RenderWindow *mainWindow)
{
	window = mainWindow;
}

sf::Vector2i Tile::GetSize(){ return sf::Vector2i(width, height); }

void Tile::IDChangeInfo(int ID, bool allowed, int layer, int page)
{
	selectedID = ID;
	changeAllowed = !allowed;
	if (layer > 1)
		changeAllowed = false;
	currentLayer = layer;
	currentPage = page;
}

void Tile::SetID(int ID)
{
	mTileID = ID;
}

int Tile::GetID(){ return mTileID; }

bool Tile::GetMouseover(){ return mMouse; }

bool Tile::GetClicked(){ return mClicked; }