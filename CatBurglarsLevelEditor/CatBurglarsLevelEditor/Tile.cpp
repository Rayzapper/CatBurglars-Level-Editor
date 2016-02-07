#include "Tile.h"

static const int width = 64, height = 64;
static int selectedID = 0;
static bool changeAllowed = true;
static sf::Texture *texture;
static sf::RenderWindow *window;
static TextureHandler *textureHandler;

Tile::Tile(sf::Vector2i position, int ID, int textureID, TextureHandler *textures)
: Entity(position, sf::IntRect(position.x, position.y, width, height)), mTileID(ID)
{
	textureHandler = textures;
	texture = textureHandler->GetTexture(textureID);
	mSprite.setTexture(*texture, true);
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
			if (changeAllowed)
			{
				mTileID = selectedID;
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

void Tile::IDChangeInfo(int ID, bool allowed, int layer)
{
	selectedID = ID;
	changeAllowed = !allowed;
	if (layer != 0)
		changeAllowed = false;
}

void Tile::SetID(int ID)
{
	mTileID = ID;
}

int Tile::GetID(){ return mTileID; }

bool Tile::GetMouseover(){ return mMouse; }

bool Tile::GetClicked(){ return mClicked; }