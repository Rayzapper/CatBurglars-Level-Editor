#include "Editor.h"

static sf::RenderWindow *window;
static const int screenWidth = 1000, screenHeight = 800, sidebarTilesX = 3, sidebarTilesY = 4;
static bool startMenu = true, load;

typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;
TileLayer tileLayerBottom, tileLayer2, tileLayer3;

static UIElement *sidebar, *selector, *sidebarSelection, *sidebarTiles;
static vector<vector<Button*>> sidebarTileButtons;

static int selectedLayer = 0, selectedTileID = 0, currentMapSizeX, currentMapSizeY;
static TextureHandler textures;

static sf::Vector2i mousePosition;

Editor::Editor()
{
	window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "CatBurglars Level Editor");
	window->setVerticalSyncEnabled(true);
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
	mousePosition = sf::Mouse::getPosition(*window);
	sidebar->Update(mousePosition);
	Tile::IDChangeInfo(selectedTileID, sidebar->GetMouseover());
	if (!startMenu)
	{
		for (TileLayer::size_type y = 0; y < tileLayerBottom.size(); y++)
		{
			for (TileRow::size_type x = 0; x < tileLayerBottom[y].size(); x++)
			{
				tileLayerBottom[y][x]->Update(mousePosition);
				if (tileLayerBottom[y][x]->GetMouseover())
				{
					sf::Vector2i newSelectPos = tileLayerBottom[y][x]->GetPosition();
					newSelectPos += Tile::GetSize() / 2;
					selector->SetPosition(newSelectPos);
				}
			}
		}
		for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
		{
			for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
			{
				sidebarTileButtons[y][x]->Update(mousePosition);
				if (sidebarTileButtons[y][x]->GetPressed())
				{
					sf::Vector2i newSelectPos = sidebarTileButtons[y][x]->GetPosition();
					newSelectPos += Tile::GetSize() / 2;
					sidebarSelection->SetPosition(newSelectPos);
					selectedTileID = sidebarTilesX * y + x;
				}
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
		selector->Render();
		sidebar->Render();
		sidebarTiles->Render();
		sidebarSelection->Render();
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
	selector = new UIElement(sf::Vector2i(200 + Tile::GetSize().x / 2, Tile::GetSize().y / 2), Tile::GetSize().x, Tile::GetSize().y, 2, &textures);
	sidebar = new UIElement(sidebarPosition, 200, 800, 1, &textures);
	sidebarTiles = new UIElement(sf::Vector2i(sidebarPosition.x, 25 + sidebarTilesY * 25), 0, 0, 0, &textures);
	sidebarSelection = new UIElement(sf::Vector2i(25 + Tile::GetSize().x / 2, 25 + Tile::GetSize().y / 2), Tile::GetSize().x, Tile::GetSize().y, 2, &textures);
	int baseX = 50, baseY = 50;
	for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
	{
		vector<Button*> row;
		for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
		{
			sf::Vector2i position(baseX * x + 25, baseY * y + 25);
			Button *button = new Button(position, Tile::GetSize().x, Tile::GetSize().y, 0);
			row.push_back(button);
		}
		sidebarTileButtons.push_back(row);
	}
}