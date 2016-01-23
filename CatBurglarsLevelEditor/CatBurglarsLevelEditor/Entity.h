#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

using namespace std;

class Entity
{
public:
	Entity(sf::Vector2i position);
	~Entity();
	virtual void Update() = 0;
	virtual void Render() = 0;
	void SetPosition(sf::Vector2i newPosition);
	sf::Vector2i GetPosition();
protected:
	sf::Vector2i mPosition, mTexturePosition;
	sf::Sprite mSprite;
};

#endif