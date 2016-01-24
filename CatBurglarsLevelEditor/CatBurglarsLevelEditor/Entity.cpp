#include "Entity.h"

Entity::Entity(sf::Vector2i position, sf::IntRect rect)
: mPosition(position), mHitBox(rect)
{

}

Entity::~Entity()
{

}

void Entity::SetPosition(sf::Vector2i newPosition)
{
	mPosition = newPosition;
}

void Entity::ChangePosition(sf::Vector2i change)
{
	mPosition -= change;
}

sf::Vector2i Entity::GetPosition(){ return mPosition; }