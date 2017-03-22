#include "../Headers/component.hpp"

namespace GUI{

Component::Component()
	: mIsSelected(false)
	, mIsActive(false)
	, size(0, 0)
{
}

Component::Component(int x, int y)
	: Component()
{
	size = sf::Vector2i(x, y);
}

Component::~Component(){
}

bool Component::isSelected() const{
	return mIsSelected;
}

void Component::select(){
	mIsSelected = true;
}

void Component::deselect(){
	mIsSelected = false;
}

bool Component::isActive() const{
	return mIsActive;
}

void Component::activate(){
	mIsActive = true;
}

void Component::deactivate(){
	mIsActive = false;
}

void Component::setSize(int x, int y){
	size = sf::Vector2i(x, y);
}

sf::Vector2i Component::getSize(){
	return size;
}

bool Component::hasSize(){
	return (size.x != 0) || (size.y != 0);
}

}