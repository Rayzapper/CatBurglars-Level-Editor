#include "Editor.h"

sf::RenderWindow *window;
Map *map;
static bool startMenu;

Editor::Editor()
{
	Initialize();
}

Editor::~Editor()
{

}

void Editor::Initialize()
{
	UIManager::Initialize();
	Tile::Initialize();
}

void Editor::Run()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "Cat Burglars Level Editor");

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