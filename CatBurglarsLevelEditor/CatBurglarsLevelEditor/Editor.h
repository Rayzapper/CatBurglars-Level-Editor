#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "Map.h"

class Editor
{
public:
	Editor();
	~Editor();
	void Run();
private:
	void Update();
	void Render();
	sf::RenderWindow *mWindow;
	Map *mMap;
};

#endif