#include "Editor.h"

Editor::Editor()
{

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

		mWindow->clear();

		mWindow->display();
	}
}