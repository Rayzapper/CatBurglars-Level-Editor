#include "Tile.h"

static const int width = 50, height = 50;
static sf::Texture texture;

Tile::Tile()
{
	
}

Tile::~Tile()
{

}

void Tile::Render(sf::RenderWindow *window)
{
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
}

void Tile::Initialize()
{
	if (!texture.loadFromFile("Resources/TestTile.png"))
	{
		//Error code
	}
}

sf::Vector2i Tile::GetSize(){ return sf::Vector2i(width, height); }

void Tile::SetID(int ID)
{
	mTileID = ID;
}

int Tile::GetID(){ return mTileID; }