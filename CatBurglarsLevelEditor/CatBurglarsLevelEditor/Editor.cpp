#include "Editor.h"

static sf::RenderWindow *window;
static sf::View *mainView, *sidebarView;
static const int screenWidth = 1056, screenHeight = 800, sidebarTilesX = 3, sidebarTilesY = 8, sidebarTilesY2 = 7, sidebarWidth = 256, tileSize = 64, sidebarObjectsX = 3, sidebarObjectsY = 4;
static bool load, focus;
static string mapName;

typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;
static TileLayer tileLayerBottom, tileLayerFront;
static vector<Object*> objectLayer1, objectLayer2;

static UIElement *sidebar, *selector, *sidebarSelection, *sidebarTiles, *sidebarTiles2, *sidebarObjects, *saveUI, *layerUI, *pageUI;
static Button *saveButton;
static vector<Button*> layerButtons, pageButtons;
static vector<vector<Button*>> sidebarTileButtons;

static int selectedLayer = 0, selectedTileID = 0, currentMapSizeX, currentMapSizeY, editorPage = 0;

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
	window->setFramerateLimit(60);
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
		else
		{
			sf::Time time = sf::milliseconds(10);
			sf::sleep(time);
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
	sf::Vector2i mouseScreenPosition = mousePosition;
	sf::Vector2f mouseWorldPosition = window->mapPixelToCoords(mousePosition, *mainView);
	mousePosition.x = mouseWorldPosition.x;
	mousePosition.y = mouseWorldPosition.y;

	sidebar->Update(mouseScreenPosition);

	bool mouseOverSidebar = sidebar->GetMouseover();
	Tile::IDChangeInfo(selectedTileID, mouseOverSidebar, selectedLayer, editorPage);
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
				if (selectedLayer > 1 && tileLayerBottom[y][x]->GetClicked() && !mouseOverSidebar)
				{
					vector<Object*>* layer;

					if (selectedLayer == 2)
						layer = &objectLayer1;
					else
						layer = &objectLayer2;

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
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 1, "null", "null", -1, &textures);
							object->SetChannel(ChannelSet(1));
						}
						if (selectedTileID == 2)
						{
							//Button
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 5, "null", "null", 0, &textures);
							object->SetChannel(ChannelSet(0));
							object->SetButtonHold(ButtonHoldSet());
						}
						if (selectedTileID == 3)
						{
							//Crate
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 6, "null", "null", -1, &textures);
						}
						if (selectedTileID == 4)
						{
							//Door
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 9, "null", "null", -1, &textures);
							object->SetChannel(ChannelSet(0));
							object->SetFacing(FacingSet());
						}
						if (selectedTileID == 5)
						{
							//Guard
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 10, "null", "null", -1, &textures);
							object->SetScript(ScriptSet());
						}
						if (selectedTileID == 6)
						{
							//ToggleButton
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 13, "null", "null", 0, &textures);
							object->SetChannel(ChannelSet(0));
							object->SetButtonHold(ButtonHoldSet());
						}
						if (selectedTileID == 7)
						{
							//Camera
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 14, "null", "null", -1, &textures);
							object->SetChannel(ChannelSet(0));
							object->SetFacing(FacingSet());
							object->SetRange(RangeSet(0));
						}
						if (selectedTileID == 8)
						{
							//Computer
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 15, "null", "null", -1, &textures);
							object->SetChannel(ChannelSet(0));
							object->SetRange(RangeSet(2));
							if (object->GetRange() == 0)
								object->SetButtonHold(ButtonHoldSet());
						}
						if (selectedTileID == 9)
						{
							//MultiDoor
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 16, "null", "null", -1, &textures);
							object->SetChannel(ChannelSet(0));
							object->SetFacing(FacingSet());
							object->SetRange(RangeSet(1));
						}
						if (selectedTileID == 10)
						{
							//MetalCrate
							object = new Object(tileLayerBottom[y][x]->GetPosition(), sf::IntRect(0, 0, 0, 0), selectedLayer, selectedTileID, 17, "null", "null", -1, &textures);
						}
						layer->push_back(object);
					}
				}
			}
		}
	}
	for (TileLayer::size_type y = 0; y < tileLayerFront.size(); y++)
	{
		for (TileRow::size_type x = 0; x < tileLayerFront[y].size(); x++)
		{
			tileLayerFront[y][x]->Update(mousePosition);
		}
	}
	for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
	{
		for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
		{
			sidebarTileButtons[y][x]->Update(mouseScreenPosition);
			if (sidebarTileButtons[y][x]->GetPressed())
			{
				sf::Vector2i newSelectPos = sidebarTileButtons[y][x]->GetPosition();
				newSelectPos += Tile::GetSize() / 2;
				sidebarSelection->SetPosition(newSelectPos);
				selectedTileID = sidebarTilesX * y + x;
			}
		}
	}
	saveUI->Update(mouseScreenPosition);
	layerUI->Update(mouseScreenPosition);
	pageUI->Update(mouseScreenPosition);
	saveButton->Update(mouseScreenPosition);
	if (saveButton->GetPressed())
	{
		SaveMap();
	}
	for (vector<Button*>::size_type i = 0; i < layerButtons.size(); i++)
	{
		layerButtons[i]->Update(mouseScreenPosition);
		if (layerButtons[i]->GetPressed())
		{
			selectedLayer = i;
			selectedTileID = 0;
			editorPage = 0;
			sidebarSelection->SetPosition(sf::Vector2i(tileSize, tileSize));
			for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
			{
				for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
				{
					bool state;
					if (selectedLayer == 0)
					{
						if (y == 0)
						{
							if (x == 2)
								state = false;
							else
								state = true;
						}
						else if (y > 3)
							state = true;
						else
							state = false;
					}
					else if (selectedLayer == 1)
					{
						if (y == 0)
						{
							if (x == 0)
								state = true;
							else
								state = false;
						}
						else if (y > 3)
							state = false;
						else
							state = true;
					}
					else if (selectedLayer == 2)
					{
						if (y > 2)
							state = false;
						else if (y == 2 && x == 0)
							state = true;
						else if (y == 0)
						{
							if (x == 1)
								state = false;
							else
								state = true;
						}
						else
							state = false;
					}
					else
					{
						if (y > 3)
							state = false;
						else if (y == 3 && x == 2)
							state = false;
						else if (y == 2 && x == 0)
							state = false;
						else if (y == 0 && x == 2)
							state = false;
						else
							state = true;
					}
					sidebarTileButtons[y][x]->SetActive(state);
				}
			}
		}
	}
	if (selectedLayer < 2)
		for (vector<Button*>::size_type i = 0; i < pageButtons.size(); i++)
		{
			pageButtons[i]->Update(mouseScreenPosition);
			if (pageButtons[i]->GetPressed())
			{
				editorPage = i;
				selectedTileID = 0;
				sidebarSelection->SetPosition(sf::Vector2i(tileSize, tileSize));
				for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
				{
					for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
					{
						bool state;
						if (editorPage == 0)
						{
							if (selectedLayer == 0)
							{
								if (y == 0)
								{
									if (x == 2)
										state = false;
									else
										state = true;
								}
								else if (y > 3)
									state = true;
								else
									state = false;
							}
							else
							{
								if (y == 0)
								{
									if (x == 0)
										state = true;
									else
										state = false;
								}
								else if (y > 3)
									state = false;
								else
									state = true;
							}
						}
						else
						{
							if (selectedLayer == 0)
							{
								if (y == 0 && x == 0)
									state = true;
								else
									state = false;
							}
							else
							{
								if (y < 6)
									state = true;
								else if (y == 6 && x == 0)
									state = true;
								else
									state = false;
							}
						}
						sidebarTileButtons[y][x]->SetActive(state);
					}
				}
			}
		}
}

void Editor::Render()
{
	sf::Color windowColor(100, 100, 100, 255);
	window->clear(windowColor);
	window->setView(*mainView);
	for (TileLayer::size_type y = 0; y < tileLayerBottom.size(); y++)
	{
		for (TileRow::size_type x = 0; x < tileLayerBottom[y].size(); x++)
		{
			tileLayerBottom[y][x]->Render(255);
		}
	}
	for (TileLayer::size_type y = 0; y < tileLayerFront.size(); y++)
	{
		for (TileRow::size_type x = 0; x < tileLayerFront[y].size(); x++)
		{
			int alpha = 255;
			if (selectedLayer < 1)
				alpha = 127;
			tileLayerFront[y][x]->Render(alpha);
		}
	}
	for (vector<Object*>::size_type i = 0; i < objectLayer1.size(); i++)
	{
		int alpha = 255;
		if (selectedLayer < 2)
			alpha = 127;
		objectLayer1[i]->Render(alpha);
	}
	for (vector<Object*>::size_type i = 0; i < objectLayer2.size(); i++)
	{
		int alpha = 255;
		if (selectedLayer < 3)
			alpha = 127;
		objectLayer2[i]->Render(alpha);
	}
	selector->Render(255);

	window->setView(*sidebarView);

	sf::RectangleShape sidebar;
	if (selectedLayer == 0)
		sidebar.setFillColor(sf::Color::Red);
	else if (selectedLayer == 1)
		sidebar.setFillColor(sf::Color::Yellow);
	else if (selectedLayer == 2)
		sidebar.setFillColor(sf::Color::Blue);
	else
		sidebar.setFillColor(sf::Color::Green);
	sidebar.setSize(sf::Vector2f(sidebarWidth, screenHeight));
	sidebar.setPosition(0, 0);
	window->draw(sidebar);

	saveUI->Render(255);
	layerUI->Render(255);
	if (selectedLayer < 2)
		pageUI->Render(255);

	if (selectedLayer < 2)
	{
		if (editorPage == 0)
			sidebarTiles->Render(255);
		else if (editorPage == 1)
			sidebarTiles2->Render(255);
	}
	else
		sidebarObjects->Render(255);

	sf::Sprite inactiveSprite;
	sf::Texture *texture;
	texture = textures.GetTexture(7);
	inactiveSprite.setTexture(*texture, true);
	inactiveSprite.setColor(sf::Color::Black);
	for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
	{
		for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
		{
			if (!sidebarTileButtons[y][x]->GetActive())
			{
				inactiveSprite.setPosition(tileSize / 2 + tileSize * x, tileSize / 2 + tileSize * y);
				window->draw(inactiveSprite);
			}
		}
	}

	sidebarSelection->Render(255);

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
				Tile *tile = new Tile(sf::Vector2i(sidebarWidth + x * tileSize, y * tileSize), 0, &textures, 0, 0);
				row.push_back(tile);
			}
			tileLayerBottom.push_back(row);
		}
		for (int y = 0; y < currentMapSizeY; y++)
		{
			TileRow row;
			for (int x = 0; x < currentMapSizeX; x++)
			{
				Tile *tile = new Tile(sf::Vector2i(sidebarWidth + x * tileSize, y * tileSize), 0, &textures, 1, 0);
				row.push_back(tile);
			}
			tileLayerFront.push_back(row);
		}
	}
	//-----------------------------------------------------Laddningskod----------------------------------------------------------------------------------------------------
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
		cout << "Background Tiles:" << endl;
		for (int y = 0; y < currentMapSizeY; y++)
		{
			TileRow row;
			for (int x = 0; x < currentMapSizeX; x++)
			{
				inputFile >> input;
				int ID = stoi(input), page;
				if (ID < 10)
					cout << " " << ID;
				else
					cout << ID;
				if (ID >= sidebarTilesX * sidebarTilesY)
					page = 1;
				else
					page = 0;
				cout << " ";
				Tile *tile = new Tile(sf::Vector2i(sidebarWidth + x * tileSize, y * tileSize), ID, &textures, 0, page);
				row.push_back(tile);
			}
			tileLayerBottom.push_back(row);
			cout << endl;
		}
		for (int y = 0; y < currentMapSizeY; y++)
		{
			TileRow row;
			for (int x = 0; x < currentMapSizeX; x++)
			{
				inputFile >> input;
				int ID = stoi(input), page;
				if (ID < 10)
					cout << " " << ID;
				else
					cout << ID;
				if (ID >= sidebarTilesX * sidebarTilesY)
					page = 1;
				else
					page = 0;
				cout << " ";
				Tile *tile = new Tile(sf::Vector2i(sidebarWidth + x * tileSize, y * tileSize), ID, &textures, 1, page);
				row.push_back(tile);
			}
			tileLayerFront.push_back(row);
			cout << endl;
		}
		inputFile >> input;
		int objNum = stoi(input);
		for (int i = 0; i < objNum; i++)
		{
			Object *object;
			int ID, xPos, yPos, channel, layer, textureID, hold;
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
			inputFile >> input;
			hold = stoi(input);

			textureID = LoadObjectTextureID(ID);

			sf::Vector2i position(xPos * tileSize + sidebarWidth, yPos * tileSize);
			object = new Object(position, sf::IntRect(0, 0, 0, 0), layer, ID + 1, textureID, "null", "null", hold, &textures);
			object->SetChannel(channel);
			objectLayer1.push_back(object);
		}
		inputFile >> input;
		objNum = stoi(input);
		for (int i = 0; i < objNum; i++)
		{
			Object *object;
			int ID, xPos, yPos, channel, layer, textureID, range;
			string script, facing;
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
			inputFile >> input;
			script = input;
			inputFile >> input;
			facing = input;
			inputFile >> input;
			range = stoi(input);

			textureID = LoadObjectTextureID(ID);

			sf::Vector2i position(xPos * tileSize + sidebarWidth, yPos * tileSize);
			object = new Object(position, sf::IntRect(0, 0, 0, 0), layer, ID + 1, textureID, script, facing, -1, &textures);
			object->SetChannel(channel);
			object->SetRange(range);
			objectLayer2.push_back(object);
		}
	}
}

int Editor::LoadObjectTextureID(int ID)
{
	int textureID = -1;
	if (ID == 0)
		textureID = 1;
	else if (ID == 1)
		textureID = 5;
	else if (ID == 2)
		textureID = 6;
	else if (ID == 3)
		textureID = 9;
	else if (ID == 4)
		textureID = 10;
	else if (ID == 5)
		textureID = 13;
	else if (ID == 6)
		textureID = 14;
	else if (ID == 7)
		textureID = 15;
	else if (ID == 8)
		textureID = 16;
	else if (ID == 9)
		textureID = 17;
	return textureID;
}

void Editor::UISpawn()
{
	sf::Vector2i sidebarPosition(sidebarWidth / 2, screenHeight / 2);
	selector = new UIElement(sf::Vector2i(sidebarWidth + tileSize / 2, tileSize / 2), tileSize, tileSize, 2, &textures);
	sidebar = new UIElement(sidebarPosition, sidebarWidth, screenHeight, 0, &textures);
	sidebarTiles = new UIElement(sf::Vector2i(sidebarPosition.x, tileSize / 2 + sidebarTilesY * tileSize / 2), 0, 0, 0, &textures);
	sidebarTiles2 = new UIElement(sf::Vector2i(sidebarPosition.x, tileSize / 2 + sidebarTilesY2 * tileSize / 2), 0, 0, 11, &textures);
	sidebarObjects = new UIElement(sf::Vector2i(sidebarPosition.x, tileSize / 2 + sidebarObjectsY * tileSize / 2), 0, 0, 8, &textures);
	sidebarSelection = new UIElement(sf::Vector2i(tileSize, tileSize), tileSize, tileSize, 2, &textures);
	for (vector<vector<Button*>>::size_type y = 0; y < sidebarTilesY; y++)
	{
		vector<Button*> row;
		for (vector<Button*>::size_type x = 0; x < sidebarTilesX; x++)
		{
			sf::Vector2i position(tileSize * x + tileSize / 2, tileSize * y + tileSize / 2);
			Button *button = new Button(position, tileSize, tileSize);
			bool state;
			if (y == 0)
			{
				if (x == 2)
					state = false;
				else
					state = true;
			}
			else if (y > 3)
				state = true;
			else
				state = false;
			button->SetActive(state);
			row.push_back(button);
		}
		sidebarTileButtons.push_back(row);
	}
	saveUI = new UIElement(sf::Vector2i(sidebarWidth / 2 - 50, 10), 100, 20, 3, &textures);
	saveButton = new Button(sf::Vector2i(sidebarWidth / 2 - 100, 0), 100, 20);
	layerUI = new UIElement(sf::Vector2i(sidebarWidth / 2 + 50, 10), 100, 20, 4, &textures);
	pageUI = new UIElement(sf::Vector2i(10, 150), 20, 100, 12, &textures);
	for (vector<Button*>::size_type i = 0; i < 4; i++)
	{
		sf::Vector2i position(sidebarWidth / 2 + 25 * i, 0);
		Button *button = new Button(position, 25, 20);
		layerButtons.push_back(button);
	}
	for (vector<Button*>::size_type i = 0; i < 2; i++)
	{
		sf::Vector2i position(0, 100 + 50 * i);
		Button *button = new Button(position, 20, 50);
		pageButtons.push_back(button);
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
		for (TileLayer::size_type y = 0; y < tileLayerFront.size(); y++)
		{
			for (TileRow::size_type x = 0; x < tileLayerFront[y].size(); x++)
			{
				int ID = tileLayerFront[y][x]->GetID();
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
			outputFile << object->GetButtonHold() << endl;
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
			outputFile << object->GetScript() << endl;
			outputFile << object->GetFacing() << endl;
			outputFile << object->GetRange() << endl;
		}
		cout << "Done!" << endl;
	}
}

int Editor::ChannelSet(int type)
{
	int channel = -1;
	if (type == 0)
		while (channel < 0)
		{
			cout << "Please enter the channel number you wish to use. (positive)" << endl;
			cin >> channel;
		}
	else
		while (channel < 1 || channel > 4)
		{
			cout << "Please enter the cat number. (1 to 4)" << endl;
			cin >> channel;
		}
	return channel;
}

string Editor::ScriptSet()
{
	string script = "null";
	while (script == "null")
	{
		cout << "Please enter the script name you wish to use. (Do not enter null!)" << endl;
		cin >> script;
	}
	return script;
}

string Editor::FacingSet()
{
	string facing = "null";
	while (facing != "N" && facing != "W" && facing != "S" && facing != "E")
	{
		cout << "Please enter the direction you want the object to face. (N, W, S or E)" << endl;
		cin >> facing;
	}
	return facing;
}

int Editor::ButtonHoldSet()
{
	int hold = -1;
	while (hold < 0)
	{
		cout << "Please enter the holdlength of the button. (in positive milliseconds)" << endl;
		cin >> hold;
	}
	return hold;
}

int Editor::RangeSet(int type)
{
	int range = -1;
	if (type < 2)
		while (range < 0)
		{
			if (type == 0)
				cout << "Please enter the range of the object. (in tiles)" << endl;
			else
				cout << "Please enter the range of channels for the object. (positive)" << endl;
			cin >> range;
		}
	else
	{
		while (range < 0 || range > 1)
		{
			cout << "Please enter whether or not the object is a toggle. (0 for hold, 1 for toggle)" << endl;
			cin >> range;
		}
	}
	return range;
}