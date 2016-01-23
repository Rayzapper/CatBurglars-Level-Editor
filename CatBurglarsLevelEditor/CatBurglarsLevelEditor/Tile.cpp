#include "Tile.h"

static const int width = 50, height = 50;
static sf::Texture *texture;
static sf::RenderWindow *window;

Tile::Tile(sf::Vector2i position)
: Entity(position), mHitBox(0, 0, width, height)
{
	
}

Tile::~Tile()
{

}

void Tile::Render()
{
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
}

void Tile::Initialize(sf::Texture *tex, sf::RenderWindow *mainWindow)
{
	window = mainWindow;
	texture = tex;
}

sf::Vector2i Tile::GetSize(){ return sf::Vector2i(width, height); }

void Tile::SetID(int ID)
{
	mTileID = ID;
}

int Tile::GetID(){ return mTileID; }