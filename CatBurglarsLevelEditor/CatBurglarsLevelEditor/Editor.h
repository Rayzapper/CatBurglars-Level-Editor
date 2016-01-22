#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>

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

};

#endif