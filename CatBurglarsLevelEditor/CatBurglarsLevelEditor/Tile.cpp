#include "Tile.h"

static const int width = 50, height = 50;
static sf::Texture *texture;
static sf::RenderWindow *window;
static TextureHandler *textureHandler;

Tile::Tile(sf::Vector2i position, int ID, int textureID, TextureHandler *textures)
: Entity(position, sf::IntRect(position.x, position.y, width, height)), mTileID(ID)
{
	textureHandler = textures;
	texture = textureHandler->GetTexture(textureID);
	mSprite.setTexture(*texture, true);
}

Tile::~Tile()
{

}

void Tile::Update()
{
	
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

void Tile::SetID(int ID)
{
	mTileID = ID;
}

int Tile::GetID(){ return mTileID; }