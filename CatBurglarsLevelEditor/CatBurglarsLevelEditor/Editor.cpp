#include "Editor.h"

Editor::Editor()
{
	mMap = new Map();
	delete mMap;
	mMap = new Map();
}

Editor::~Editor()
{

}

void Editor::Run()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(800, 800), "Cat Burglars Level Editor");

	while (mWindow->isOpen())
	{
		sf::Event event;
		while (mWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mWindow->close();
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
	mWindow->clear();

	mWindow->display();
}