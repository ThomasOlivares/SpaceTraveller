#include "../Headers/viewNode.hpp"
#include "../Headers/spriteNode.hpp"
#include "../Headers/command.hpp"
#include "../Headers/entity.hpp"
#include "../Headers/category.hpp"
#include "../Headers/planet.hpp"
#include "../Headers/cursor.hpp"

#include <SFML/Graphics.hpp>


#include <iostream>

struct PlanetDisplayIntel
{
	PlanetDisplayIntel(sf::Vector2f position_, bool clicked_)
	: position(position_)
	, clicked(clicked_)
	{
	}

	void operator() (Planet& planet, sf::Time) const{
		planet.select(position, clicked);
	}

	bool clicked;
	sf::Vector2f position;
};

struct CursorDisplay
{
	CursorDisplay(sf::Vector2f position_, bool clicked_)
	: position(position_)
	, clicked(clicked_)
	{
	}

	void operator() (Cursor& cursor, sf::Time) const{
		cursor.select(position, clicked);
	}

	bool clicked;
	sf::Vector2f position;
};

ViewNode::ViewNode(const sf::View &initialView, sf::RenderTarget& window_) 
: SceneNode(Category::View)
, mView(initialView)
, window(window_)
, zoom(1)
, newCommand(false)
{
}

void ViewNode::zoomView(const float factor){
	mView.zoom(factor);
	zoom *= factor;
}

void ViewNode::updateCurrent(sf::Time, CommandQueue& commands)
{	
	if (newCommand){
		commands.push(displayPlanets);
		commands.push(displayCursor);
		newCommand = false;
	}
}


void ViewNode::drawCurrent(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.setView(mView);
}

unsigned int ViewNode::getCategory() const
{
	return Category::View;
}

void ViewNode::moveView(sf::Vector2f movement){
	mView.move(-movement.x*zoom, -movement.y*zoom);
}

void ViewNode::handleEvent(sf::Vector2f mousePosition, bool clicked){
	window.setView(mView);

	sf::Vector2i mousePosition_ = static_cast<sf::Vector2i>(mousePosition);
	mouseOnSpace = window.mapPixelToCoords(mousePosition_);

	displayPlanets.category = Category::Planet;
	displayPlanets.action = derivedAction<Planet>(PlanetDisplayIntel(mouseOnSpace, 
		clicked));

	displayCursor.category = Category::Cursor;
	displayCursor.action = derivedAction<Cursor>(CursorDisplay(mouseOnSpace, 
		clicked));

	newCommand = true;
}
