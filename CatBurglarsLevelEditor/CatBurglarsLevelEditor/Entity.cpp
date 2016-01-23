#include "Entity.h"

Entity::Entity(sf::Vector2i position)
: mPosition(position)
{

}

Entity::~Entity()
{

}

void Entity::SetPosition(sf::Vector2i newPosition)
{
	mPosition = newPosition;
}

sf::Vector2i Entity::GetPosition(){ return mPosition; }