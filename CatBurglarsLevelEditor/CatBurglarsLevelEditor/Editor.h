#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "UIManager.h"
#include "Map.h"
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
};

#endif