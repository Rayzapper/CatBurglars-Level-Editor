#include "Editor.h"

static sf::RenderWindow *window;
static const int screenWidth = 800, screenHeight = 800;
static bool startMenu = true, load;
static sf::Texture tileTexture;

typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;
TileLayer tileLayerBottom, tileLayer2, tileLayer3;

static int selectedLayer = 0, currentMapSizeX, currentMapSizeY;

Editor::Editor()
{
	StartConfiguration();
	StartMapSpawn();
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
			for (TileRow::size_type j = 0; j < tileLayerBottom[i].size(); j++)
			{
				tileLayerBottom[i][j]->Render();
			}
		}
		for (TileLayer::size_type i = 0; i < tileLayer2.size(); i++)
		{
			for (TileRow::size_type j = 0; j < tileLayer2[i].size(); j++)
			{
				tileLayer2[i][j]->Render();
			}
		}
		for (TileLayer::size_type i = 0; i < tileLayer3.size(); i++)
		{
			for (TileRow::size_type j = 0; j < tileLayer3[i].size(); j++)
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
	string input;
	while (input != "New" && input != "Load")
	{
		cout << "Please type 'New' for a new map or 'Load' to load a map." << endl;
		cin >> input;
	}
	if (input == "New") load = false;
	if (input == "load") load = true;
	if (!load)
	{
		cout << "Please enter map width." << endl;
		cin >> currentMapSizeX;
		cout << "Please enter map height." << endl;
		cin >> currentMapSizeY;
	}
	else
	{
		cout << "Please enter the name of the map." << endl;
		cin >> input;
	}
}

void Editor::StartMapSpawn()
{
	if (!load)
	{
		for (int y = 0; y < currentMapSizeX; y++)
		{
			TileRow row;
			for (int x = 0; x < currentMapSizeY; x++)
			{
				Tile *tile = new Tile(sf::Vector2i(x * Tile::GetSize().x, y * Tile::GetSize().y), 0);
				row.push_back(tile);
			}
			tileLayerBottom.push_back(row);
		}
	}
	else
	{

	}
}