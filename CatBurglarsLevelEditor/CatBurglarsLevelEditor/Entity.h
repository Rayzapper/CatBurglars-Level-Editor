#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

using namespace std;

class Entity
{
public:
	Entity();
	~Entity();
	virtual void Render(sf::RenderWindow *window) = 0;
protected:
	sf::Vector2i mPosition;
	sf::Sprite mSprite;
};

#endif