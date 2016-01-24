#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "TextureHandler.h"

using namespace std;

class Entity
{
public:
	Entity(sf::Vector2i position, sf::IntRect rect);
	~Entity();
	virtual void Update(sf::Vector2i mousePosition) = 0;
	virtual void Render() = 0;
	void SetPosition(sf::Vector2i newPosition);
	void ChangePosition(sf::Vector2i change);
	sf::Vector2i GetPosition();
protected:
	sf::Vector2i mPosition, mTexturePosition;
	sf::Sprite mSprite;
	sf::IntRect mHitBox;
	bool mMouse = false;
};

#endif