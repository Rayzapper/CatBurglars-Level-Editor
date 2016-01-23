#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

using namespace std;

class Entity
{
public:
	Entity(sf::Vector2i position);
	~Entity();
	virtual void Render() = 0;
protected:
	sf::Vector2i mPosition, mTexturePosition;
	sf::Sprite mSprite;
};

#endif