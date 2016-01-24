#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "UIElement.h"
#include "Button.h"
#include "Tile.h"
#include "TextureHandler.h"

class Editor
{
public:
	Editor();
	~Editor();
	void Run();
private:
	void Initialize();
	void Update();
	void Render();
	void StartConfiguration();
	void StartMapSpawn(string name);
	void UISpawn();
	void SaveMap();
};

#endif