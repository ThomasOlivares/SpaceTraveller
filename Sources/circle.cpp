#include "../Headers/circle.hpp"
#include "../Headers/utility.hpp"

#include <iostream>

Circle::Circle()
: center(sf::Vector2f(0, 0))
, radius(0)
{
}

Circle::Circle(const Circle& circle)
: center(circle.getCenter())
, radius(circle.getRadius())
{
}

Circle::Circle(sf::Vector2f center_, float radius_)
: center(center_)
, radius(radius_)
{
}

float Circle::getRadius() const{
	return radius;
}

void Circle::setRadius(float radius_){
	radius = radius_;
}

sf::Vector2f Circle::getCenter() const{
	return center;
}

void Circle::setCenter(sf::Vector2f center_){
	center = center_;
}

bool Circle::contain(sf::Vector2f point){
	return distance(point, center) <= radius;
}