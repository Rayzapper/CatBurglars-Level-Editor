#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "UIElement.h"
#include "Tile.h"

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
	void StartSpawn();
};

#endif