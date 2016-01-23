#include "Editor.h"

static sf::RenderWindow *window;
static const int screenWidth = 800, screenHeight = 800;
static bool startMenu;
static sf::Texture startUITexture, tileTexture;
typedef vector<Tile*> TileColumn;
typedef vector<TileColumn> TileLayer;
static TileLayer tileLayerBottom, tileLayer2, tileLayer3;
static int selectedLayer = 0, currentMapSizeX, currentMapSizeY;
static UIElement *startUIBase;
static Button *startUINew, *startUILoad;

Editor::Editor()
{
	startUITexture.loadFromFile("Resources/StartUI.png");
	tileTexture.loadFromFile("Resources/TestTile.png");
	Initialize();
}

Editor::~Editor()
{
	
}

void Editor::Initialize()
{
	UIElement::Initialize(&startUITexture, window);
	Button::Initialize(&startUITexture, window);
	Tile::Initialize(&tileTexture, window);
}

void Editor::Run()
{
	window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "CatBurglars Level Editor");
	StartSpawn();
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		Update();
		Render();
	}
}

void Editor::Update()
{

}

void Editor::Render()
{
	window->clear();
	if (!startMenu)
	{
		for (TileLayer::size_type i; i < tileLayerBottom.size(); i++)
		{
			for (TileColumn::size_type j; j < tileLayerBottom[i].size(); j++)
			{
				tileLayerBottom[i][j]->Render();
			}
		}
		for (TileLayer::size_type i; i < tileLayer2.size(); i++)
		{
			for (TileColumn::size_type j; j < tileLayer2[i].size(); j++)
			{
				tileLayer2[i][j]->Render();
			}
		}
		for (TileLayer::size_type i; i < tileLayer3.size(); i++)
		{
			for (TileColumn::size_type j; j < tileLayer3[i].size(); j++)
			{
				tileLayer3[i][j]->Render();
			}
		}
	}
	else
	{
		startUIBase->Render();
		startUINew->Render();
		startUILoad->Render();
	}
	window->display();
}

void Editor::StartSpawn()
{
	startUIBase = new UIElement(sf::Vector2i(screenWidth / 2, screenHeight / 2));
}