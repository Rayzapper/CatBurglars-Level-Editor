#include "Editor.h"

static sf::RenderWindow *window;
static sf::View *mainView, *sidebarView;
static const int screenWidth = 1056, screenHeight = 800, sidebarTilesX = 3, sidebarTilesY = 4, sidebarWidth = 256, tileSize = 64, sidebarObjectsX = 3, sidebarObjectsY = 2;
static bool load, focus;
static string mapName;

typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;
TileLayer tileLayerBottom;
vector<Object*> objectLayer1, objectLayer2;

static UIElement *sidebar, *selector, *sidebarSelection, *sidebarTiles, *sidebarObjects, *saveUI, *layerUI;
static Button *saveButton;
static vector<Button*> layerButtons;
static vector<vector<Button*>> sidebarTileButtons;

static int selectedLayer = 0, selectedTileID = 0, currentMapSizeX, currentMapSizeY;
static TextureHandler textures;

static sf::Vector2i mousePosition;

static float zoomLevel = 1.0;

sf::Font font;

Editor::Editor()
{
	window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "CatBurglars Level Editor");
	mainView = new sf::View(sf::Vector2f((screenWidth - sidebarWidth) / 2 + sidebarWidth, screenHeight / 2), sf::Vector2f(screenWidth - sidebarWidth, screenHeight));
	float sidebarRatio = (float)sidebarWidth / (float)screenWidth;
	mainView->setViewport(sf::FloatRect(sidebarRatio, 0.0, 1.0 - sidebarRatio, 1.0));
	sidebarView = new sf::View(sf::Vector2f(sidebarWidth / 2, screenHeight / 2), sf::Vector2f(sidebarWidth, screenHeight));
	sidebarView->setViewport(sf::FloatRect(0.0, 0.0, sidebarRatio, 1.0));
	window->setVerticalSyncEnabled(true);
	textures.Initialize();
	Initialize();
	StartConfiguration();
	StartMapSpawn(mapName);
}

Editor::~Editor()
{
	
}

void Editor::Initialize()
{
	font.loadFromFile("Resources/calibri.ttf");
	UIElement::Initialize(window);
	Tile::Initialize(window);
	Object::Initialize(window, &font);
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
			if (event.type == sf::Event::GainedFocus)
				focus = true;
			if (event.type == sf::Event::LostFocus)
				focus = false;
		}
		if (focus)
		{
			Update();
			Render();
		}
	}
}

void Editor::Update()
{
	sf::Vector2f viewCenter = mainView->getCenter();
	sf::Vector2f viewChange = viewCenter;
	if (currentMapSizeX > (screenWidth - sidebarWidth) / tileSize)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			viewCenter.x += 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			viewCenter.x -= 5;
		}
		if (viewCenter.x < screenWidth / 2 + sidebarWidth / 2)
			viewCenter.x = screenWidth / 2 + sidebarWidth / 2;
		if (viewCenter.x > (currentMapSizeX * tileSize) + sidebarWidth - screenWidth / 2 + sidebarWidth / 2)
			viewCenter.x = (currentMapSizeX * tileSize) + sidebarWidth - screenWidth / 2 + sidebarWidth / 2;

	}
	if (currentMapSizeY > screenHeight / tileSize)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			viewCenter.y += 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			viewCenter.y -= 5;
		}
		if (viewCenter.y < screenHeight / 2)
			viewCenter.y = screenHeight / 2;
		if (viewCenter.y >(currentMapSizeY * tileSize) - screenHeight / 2)
			viewCenter.y = (currentMapSizeY * tileSize) - screenHeight / 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		zoomLevel -= 0.02;
		if (zoomLevel < 1.0)
			zoomLevel = 1.0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		zoomLevel += 0.02;
		if (zoomLevel > 5.0)
			zoomLevel = 5.0;
	}
	mainView->setSize((float)screenWidth * zoomLevel - (float)sidebarWidth * zoomLevel, (float)screenHeight * zoomLevel);
	if (viewCenter != mainView->getCenter())
		mainView->setCenter(viewCenter);
	viewChange -= viewCenter;

	mousePosition = sf::Mouse::getPosition(*window);

	mousePosition.x += viewCenter.x - screenWidth / 2 - sidebarWidth / 2;
	mousePosition.y += viewCenter.y - screenHeight / 2;

	sidebar->Update(sf::Mouse::getPosition(*window));

	bool mouseOverSidebar = sidebar->GetMouseover();
	Tile::IDChangeInfo(selectedTileID, mouseOverSidebar, selectedLayer);
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
				if (selectedLayer != 0 && tileLayerBottom[y][x]->GetClicked() && !mouseOverSidebar)
				{
					vector<Object*>* layer;
					if (selectedLayer == 1)
						layer = &objectLayer1;
					else
						layer = &objectLayer2;
					if (selectedLayer != 0)
					{
						for (vector<Object*>::size_type i = 0; i < layer->size(); i++)
						{
							int xPos = layer->at(i)->GetMapPosition().x, yPos = layer->at(i)->GetMapPosition().y;
							if (xPos == x && yPos == y)
							{
								layer->erase(layer->begin() + i);
								i--;
							}
						}
						if (selectedTileID != 0)
						{
							Object *object;
							if (selectedTileID == 1)
							{
								//Cat
								object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 1, &textures);
							}
							if (selectedTileID == 2)
							{
								//Button
								object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 5, &textures);
								object->SetChannel(ChannelSet());
							}
							if (selectedTileID == 3)
							{
								//Crate
								object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 6, &textures);
							}
							layer->push_back(object);
						}
					}
				}
			}
		}
	}
	for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
	{
		for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
		{
			sidebarTileButtons[y][x]->Update(sf::Mouse::getPosition(*window));
			if (sidebarTileButtons[y][x]->GetPressed())
			{
				sf::Vector2i newSelectPos = sidebarTileButtons[y][x]->GetPosition();
				newSelectPos += Tile::GetSize() / 2;
				sidebarSelection->SetPosition(newSelectPos);
				selectedTileID = sidebarTilesX * y + x;
			}
		}
	}
	saveUI->Update(sf::Mouse::getPosition(*window));
	layerUI->Update(sf::Mouse::getPosition(*window));
	saveButton->Update(sf::Mouse::getPosition(*window));
	if (saveButton->GetPressed())
	{
		SaveMap();
	}
	for (vector<Button*>::size_type i = 0; i < layerButtons.size(); i++)
	{
		layerButtons[i]->Update(sf::Mouse::getPosition(*window));
		if (layerButtons[i]->GetPressed())
		{
			selectedLayer = i;
			selectedTileID = 0;
			sidebarSelection->SetPosition(sf::Vector2i(tileSize, tileSize));
			for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
			{
				for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
				{
					bool state;
					if (selectedLayer == 0)
						state = true;
					else
					{
						if (y == 0)
							state = true;
						else if (y == 1 && x == 0)
							state = true;
						else
							state = false;
					}
					sidebarTileButtons[y][x]->SetActive(state);
				}
			}
		}
	}
}

void Editor::Render()
{
	window->clear();
	window->setView(*mainView);
	for (TileLayer::size_type y = 0; y < tileLayerBottom.size(); y++)
	{
		for (TileRow::size_type x = 0; x < tileLayerBottom[y].size(); x++)
		{
			tileLayerBottom[y][x]->Render();
		}
	}
	for (vector<Object*>::size_type i = 0; i < objectLayer1.size(); i++)
	{
		objectLayer1[i]->Render();
	}
	for (vector<Object*>::size_type i = 0; i < objectLayer2.size(); i++)
	{
		objectLayer2[i]->Render();
	}
	selector->Render();

	window->setView(*sidebarView);

	sf::RectangleShape sidebar;
	sidebar.setFillColor(sf::Color::Blue);
	sidebar.setSize(sf::Vector2f(sidebarWidth, screenHeight));
	sidebar.setPosition(0, 0);
	window->draw(sidebar);

	saveUI->Render();
	layerUI->Render();

	if (selectedLayer == 0)
		sidebarTiles->Render();
	else
		sidebarObjects->Render();
	sidebarSelection->Render();
	window->display();
}

void Editor::StartConfiguration()
{
	string input;
	while (input != "n" && input != "l")
	{
		cout << "Please type 'n' for a new map or 'l' to load a map." << endl;
		cin >> input;
	}
	if (input == "n") load = false;
	if (input == "l") load = true;
	if (!load)
	{
		cout << "Please enter map width." << endl;
		cin >> currentMapSizeX;
		cout << "Please enter map height." << endl;
		cin >> currentMapSizeY;
	}
	else
	{
		cout << "Please enter the name of the map. (Case sensitive)" << endl;
		cin >> mapName;
	}
}

void Editor::StartMapSpawn(string name)
{
	if (!load)
	{
		for (int y = 0; y < currentMapSizeY; y++)
		{
			TileRow row;
			for (int x = 0; x < currentMapSizeX; x++)
			{
				Tile *tile = new Tile(sf::Vector2i(sidebarWidth + x * tileSize, y * tileSize), 0, 0, &textures);
				row.push_back(tile);
			}
			tileLayerBottom.push_back(row);
		}
	}
	else
	{
		ifstream inputFile("Maps/" + name + ".txt");
		string input;
		inputFile >> input;
		currentMapSizeX = stoi(input);
		cout << "Map width: " << currentMapSizeX << endl;
		inputFile >> input;
		currentMapSizeY = stoi(input);
		cout << "Map height: " << currentMapSizeY << endl;
		cout << "Tiles:" << endl;
		for (int y = 0; y < currentMapSizeY; y++)
		{
			TileRow row;
			for (int x = 0; x < currentMapSizeX; x++)
			{
				inputFile >> input;
				int ID = stoi(input);
				if (ID < 10)
					cout << " " << ID;
				else
					cout << ID;
				cout << " ";
				Tile *tile = new Tile(sf::Vector2i(sidebarWidth + x * tileSize, y * tileSize), ID, 0, &textures);
				row.push_back(tile);
			}
			tileLayerBottom.push_back(row);
			cout << endl;
		}
		inputFile >> input;
		int objNum = stoi(input);
		for (int i = 0; i < objNum; i++)
		{
			Object *object;
			int ID, xPos, yPos, channel, layer, textureID;
			inputFile >> input;
			ID = stoi(input);
			inputFile >> input;
			xPos = stoi(input);
			inputFile >> input;
			yPos = stoi(input);
			inputFile >> input;
			channel = stoi(input);
			inputFile >> input;
			layer = stoi(input);

			if (ID == 0)
				textureID = 1;
			else if (ID == 1)
				textureID = 5;
			else if (ID == 2)
				textureID = 6;

			sf::Vector2i position(xPos * tileSize + sidebarWidth, yPos * tileSize);
			object = new Object(position, sf::IntRect(0, 0, 0, 0), layer, ID + 1, textureID, &textures);
			object->SetChannel(channel);
			objectLayer1.push_back(object);
		}
		inputFile >> input;
		objNum = stoi(input);
		for (int i = 0; i < objNum; i++)
		{
			Object *object;
			int ID, xPos, yPos, channel, layer, textureID;
			inputFile >> input;
			ID = stoi(input);
			inputFile >> input;
			xPos = stoi(input);
			inputFile >> input;
			yPos = stoi(input);
			inputFile >> input;
			channel = stoi(input);
			inputFile >> input;
			layer = stoi(input);

			if (ID == 0)
				textureID = 1;
			else if (ID == 1)
				textureID = 5;
			else if (ID == 2)
				textureID = 6;

			sf::Vector2i position(xPos * tileSize + sidebarWidth, yPos * tileSize);
			object = new Object(position, sf::IntRect(0, 0, 0, 0), layer, ID + 1, textureID, &textures);
			object->SetChannel(channel);
			objectLayer2.push_back(object);
		}
	}
}

void Editor::UISpawn()
{
	sf::Vector2i sidebarPosition(sidebarWidth / 2, screenHeight / 2);
	selector = new UIElement(sf::Vector2i(sidebarWidth + tileSize / 2, tileSize / 2), tileSize, tileSize, 2, &textures);
	sidebar = new UIElement(sidebarPosition, sidebarWidth, screenHeight, 0, &textures);
	sidebarTiles = new UIElement(sf::Vector2i(sidebarPosition.x, tileSize / 2 + sidebarTilesY * tileSize / 2), 0, 0, 0, &textures);
	sidebarObjects = new UIElement(sf::Vector2i(sidebarPosition.x, tileSize / 2 + sidebarObjectsY * tileSize / 2), 0, 0, 8, &textures);
	sidebarSelection = new UIElement(sf::Vector2i(tileSize, tileSize), tileSize, tileSize, 2, &textures);
	for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
	{
		vector<Button*> row;
		for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
		{
			sf::Vector2i position(tileSize * x + tileSize / 2, tileSize * y + tileSize / 2);
			Button *button = new Button(position, tileSize, tileSize);
			row.push_back(button);
		}
		sidebarTileButtons.push_back(row);
	}
	saveUI = new UIElement(sf::Vector2i(sidebarWidth / 2 - 50, 10), 100, 20, 3, &textures);
	saveButton = new Button(sf::Vector2i(sidebarWidth / 2 - 100, 0), 100, 20);
	layerUI = new UIElement(sf::Vector2i(sidebarWidth / 2 + 50, 10), 100, 20, 4, &textures);
	for (vector<Button*>::size_type i = 0; i < 3; i++)
	{
		sf::Vector2i position(sidebarWidth / 2 + 33 * i, 0);
		Button *button = new Button(position, 33, 20);
		layerButtons.push_back(button);
	}
}

void Editor::SaveMap()
{
	string input;
	while (input != "n" && input != "y")
	{
		cout << "Would you like to save your map? y or n" << endl;
		cin >> input;
	}
	if (input == "y")
	{
		cout << "Please write the name of the map. (no spaces)" << endl;
		cin >> input;
		ofstream outputFile("Maps/" + input + ".txt");
		outputFile << currentMapSizeX << endl;
		outputFile << currentMapSizeY << endl;
		for (TileLayer::size_type y = 0; y < tileLayerBottom.size(); y++)
		{
			for (TileRow::size_type x = 0; x < tileLayerBottom[y].size(); x++)
			{
				int ID = tileLayerBottom[y][x]->GetID();
				if (ID < 10)
					outputFile << "0" << ID << " ";
				else
					outputFile << ID << " ";
			}
			outputFile << endl;
		}
		outputFile << objectLayer1.size() << endl;
		for (vector<Object*>::size_type i = 0; i < objectLayer1.size(); i++)
		{
			Object *object = objectLayer1[i];
			outputFile << object->GetID() - 1 << endl;
			outputFile << object->GetMapPosition().x << endl;
			outputFile << object->GetMapPosition().y << endl;
			outputFile << object->GetChannel() << endl;
			outputFile << object->GetLayer() << endl;
		}
		outputFile << objectLayer2.size() << endl;
		for (vector<Object*>::size_type i = 0; i < objectLayer2.size(); i++)
		{
			Object *object = objectLayer2[i];
			outputFile << object->GetID() - 1 << endl;
			outputFile << object->GetMapPosition().x << endl;
			outputFile << object->GetMapPosition().y << endl;
			outputFile << object->GetChannel() << endl;
			outputFile << object->GetLayer() << endl;
		}
		cout << "Done!" << endl;
	}
}

int Editor::ChannelSet()
{
	int channel = -1;
	while (channel < 0)
	{
		cout << "Please enter the channel number you wish to use. (positive)" << endl;
		cin >> channel;
	}
	return channel;
}