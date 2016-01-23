#include "Editor.h"

sf::RenderWindow *window;
static bool startMenu;
sf::Texture startUITexture, tileTexture;

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
	UIElement::Initialize(&startUITexture);
	Button::Initialize(&startUITexture);
	Tile::Initialize(&tileTexture);
}

void Editor::Run()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "CatBurglars Level Editor");

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

	window->display();
}