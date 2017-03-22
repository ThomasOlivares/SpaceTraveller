#include "../Headers/container.hpp"

#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace std;

namespace GUI
{

Container::Container()
: mChildren()
, mSelectedChild(-1)
{
}

void Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);

	if (!hasSelection() && component->isSelectable()){
		select(mChildren.size() - 1);
	}
}

bool Container::isSelectable() const
{
    return false;
}

void Container::handleEvent(const sf::Event& event)
{
    // If we have selected a child then give it events
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
	{
		mChildren[mSelectedChild]->handleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection()){
				mChildren[mSelectedChild]->activate();
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed){
		if (hasSelection()){
			mChildren[mSelectedChild]->activate();
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		selectAt(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr){
    	target.draw(*(*itr), states);
    }
}

bool Container::hasSelection() const
{
	return mSelectedChild >= 0;
}

void Container::select(std::size_t index)
{
	if (mChildren[index]->isSelectable())
	{
		if (hasSelection()){
			mChildren[mSelectedChild]->deselect();
		}

		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void Container::selectAt(sf::Vector2f mousePosition){

	if (mSelectedChild >= 0){
		mChildren[mSelectedChild]->deselect();
		mSelectedChild = -1;
	}
	
	for (int index = 0; index < mChildren.size(); index++)
	{
		Component::Ptr component = mChildren[index];

		if (component->hasSize()){

			sf::Vector2i size = component->getSize();

			// Checking if the mouse is on the component
			if (mousePosition.x >= component->getPosition().x &&
				mousePosition.y >= component->getPosition().y &&
				mousePosition.x <= component->getPosition().x + size.x &&
				mousePosition.y <= component->getPosition().y + size.y)
			{
				mSelectedChild = index;
				select(index);
			}
		}
	}
}

void Container::selectNext()
{
	if (!hasSelection()){
		return;
	}

	// Search next component that is selectable, wrap around if necessary
	int next = mSelectedChild;
	do{
		next = (next + 1) % mChildren.size();
	}
	while (!mChildren[next]->isSelectable());

	// Select that component
	select(next);
}

void Container::selectPrevious()
{
	if (!hasSelection()){
		return;
	}

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	do{
		prev = (prev + mChildren.size() - 1) % mChildren.size();
	}
	while (!mChildren[prev]->isSelectable());

	// Select that component
	select(prev);
}

}