#include "../Headers/entity.hpp"

#include <iostream>

Entity::Entity(int x, int y)
: velocity(sf::Vector2f(0, 0))
, absoluteVelocity(0.f)
{
	setPosition(x, y);
}

Entity::Entity(sf::Vector2f position)
: velocity(sf::Vector2f(0, 0))
, absoluteVelocity(0.f)
{
	setPosition(position);
}

void Entity::updateCurrent(sf::Time time, CommandQueue&)
{
	move(time.asSeconds() * absoluteVelocity * velocity);
}

void Entity::setVelocity(sf::Vector2f velocity_){
	velocity = velocity_;
}

sf::Vector2f Entity::getVelocity(){
	return velocity;
}
