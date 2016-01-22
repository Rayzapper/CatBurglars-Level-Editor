#include "Tile.h"

static const int width = 50, height = 50;

Tile::Tile()
{

}

Tile::~Tile()
{

}

void Tile::Render()
{

}

sf::Vector2i Tile::GetSize(){ return sf::Vector2i(width, height); }

void Tile::SetID(int ID)
{
	mTileID = ID;
}

int Tile::GetID(){ return mTileID; }