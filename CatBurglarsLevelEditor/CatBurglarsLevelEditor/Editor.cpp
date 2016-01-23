#include "Editor.h"

static sf::RenderWindow *window;
static const int screenWidth = 1000, screenHeight = 800;
static bool startMenu = true, load;

typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;
TileLayer tileLayerBottom, tileLayer2, tileLayer3;

static UIElement *sidebar;

static int selectedLayer = 0, currentMapSizeX, currentMapSizeY;
static TextureHandler textures;

Editor::Editor()
{
	window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "CatBurglars Level Editor");
	textures.Initialize();
	Initialize();
	StartConfiguration();
	StartMapSpawn();
	startMenu = false;
}

Editor::~Editor()
{
	
}

void Editor::Initialize()
{
	UIElement::Initialize(window);
	Button::Initialize(window);
	Tile::Initialize(window);
}

void Editor::Run()
{
	UISpawn();
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
	if (!startMenu)
	{
		for (TileLayer::size_type y = 0; y < tileLayerBottom.size(); y++)
		{
			for (TileRow::size_type x = 0; x < tileLayerBottom[y].size(); x++)
			{
				tileLayerBottom[y][x]->Update();
			}
		}
	}
}

void Editor::Render()
{
	window->clear();
	if (!startMenu)
	{
		for (TileLayer::size_type y = 0; y < tileLayerBottom.size(); y++)
		{
			for (TileRow::size_type x = 0; x < tileLayerBottom[y].size(); x++)
			{
				tileLayerBottom[y][x]->Render();
			}
		}
		sidebar->Render();
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
		for (int y = 0; y < currentMapSizeY; y++)
		{
			TileRow row;
			for (int x = 0; x < currentMapSizeX; x++)
			{
				Tile *tile = new Tile(sf::Vector2i(200 + x * Tile::GetSize().x, y * Tile::GetSize().y), 0, 0, &textures);
				row.push_back(tile);
			}
			tileLayerBottom.push_back(row);
		}
	}
	else
	{

	}
}

void Editor::UISpawn()
{
	sf::Vector2i sidebarPosition(100, screenHeight / 2);
	sidebar = new UIElement(sidebarPosition, 200, 800, 1, &textures);
}