#include "Editor.h"

static sf::RenderWindow *window;
static const int screenWidth = 800, screenHeight = 800;
static bool startMenu = true;
static sf::Texture tileTexture;
typedef vector<Tile*> TileColumn;
typedef vector<TileColumn> TileLayer;
TileLayer tileLayerBottom, tileLayer2, tileLayer3;
static int selectedLayer = 0, currentMapSizeX, currentMapSizeY;

Editor::Editor()
{
	tileTexture.loadFromFile("Resources/TestTile.png");
	window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "CatBurglars Level Editor");
	Initialize();
}

Editor::~Editor()
{
	
}

void Editor::Initialize()
{
	UIElement::Initialize(&tileTexture, window);
	Button::Initialize(&tileTexture, window);
	Tile::Initialize(&tileTexture, window);
}

void Editor::Run()
{
	StartConfiguration();
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
		for (TileLayer::size_type i = 0; i < tileLayerBottom.size(); i++)
		{
			for (TileColumn::size_type j = 0; j < tileLayerBottom[i].size(); j++)
			{
				tileLayerBottom[i][j]->Render();
			}
		}
		for (TileLayer::size_type i = 0; i < tileLayer2.size(); i++)
		{
			for (TileColumn::size_type j = 0; j < tileLayer2[i].size(); j++)
			{
				tileLayer2[i][j]->Render();
			}
		}
		for (TileLayer::size_type i = 0; i < tileLayer3.size(); i++)
		{
			for (TileColumn::size_type j = 0; j < tileLayer3[i].size(); j++)
			{
				tileLayer3[i][j]->Render();
			}
		}
	}
	else
	{
		
	}
	window->display();
}

void Editor::StartConfiguration()
{
	cout << "test" << endl;
}