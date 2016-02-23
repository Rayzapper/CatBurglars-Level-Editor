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
	//texture2 = textureHandler->GetTexture(11);
	currentPage = page;
	//if (currentPage == 0)
		mSprite.setTexture(*texture1, true);
	/*else if (currentPage == 1)
		mSprite.setTexture(*texture2, true);*/
	//if (currentPage == 0)
		mSprite.setTextureRect(sf::IntRect((ID % 3) * width, floor(ID / 3) * height, width, height));
	/*else if (currentPage == 1)
		mSprite.setTextureRect(sf::IntRect(((ID - 24) % 3) * width, floor((ID - 24) / 3) * height, width, height));*/
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
				//if (currentPage == 0)
				//{
					mSprite.setTexture(*texture1, true);
					mSprite.setTextureRect(sf::IntRect((mTileID % 3) * width, floor(mTileID / 3) * height, width, height));
				//}
				/*else if (currentPage == 1)
				{
					mSprite.setTexture(*texture2, true);
					mSprite.setTextureRect(sf::IntRect(((mTileID - 24) % 3) * width, floor((mTileID - 24) / 3) * height, width, height));
				}*/
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

void Tile::IDChangeInfo(int ID, bool allowed, int layer, int page)
{
	selectedID = ID;
	selectedID += (page * 24);
	changeAllowed = !allowed;
	if (layer == 2 || layer == 3)
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

bool Tile::GetRightClicked() { return mRightClicked; }