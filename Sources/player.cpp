#include "../Headers/player.hpp"
#include "../Headers/commandQueue.hpp"
#include "../Headers/command.hpp"
#include "../Headers/viewNode.hpp"
#include "../Headers/planet.hpp"

#include <iostream>

struct ViewZoom
{
	ViewZoom(float delta)
	: velocity(1 + 0.1*delta)
	{
	}

	void operator() (ViewNode& viewNode, sf::Time) const
	{
		viewNode.zoomView(velocity);
	}

	float velocity;
};

struct ViewMover
{
	ViewMover(sf::Vector2f movement_)
	: movement(movement_)
	{
	}

	void operator() (ViewNode& viewNode, sf::Time) const
	{
		viewNode.moveView(movement);
	}

	sf::Vector2f movement;
};

struct PlanetDisplayIntels
{
	PlanetDisplayIntels(sf::Vector2f mousePosition_, bool clicked_)
	: clicked(clicked_)
	, mousePosition(mousePosition_)
	{
	}

	void operator() (ViewNode& view, sf::Time) const
	{
		view.handleEvent(mousePosition, clicked);
	}

	sf::Vector2f mousePosition;
	bool clicked;
};

Player::Player(){
	setPosition(0, 0);
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands, State::Context context)
{
	if (event.type == sf::Event::MouseWheelMoved)
	{
		float movement = event.mouseWheel.delta;
		mActionBinding[Zoom].category = Category::View;
		mActionBinding[Zoom].action	 = derivedAction<ViewNode>(ViewZoom(movement));
		commands.push(mActionBinding[Zoom]);
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
			event.type == sf::Event::MouseMoved)
	{
		if (position.x == 0 && position.y == 0){
			setPosition(event.mouseMove.x, event.mouseMove.y);
		}
		else{
			sf::Vector2f movement = sf::Vector2f(event.mouseMove.x - position.x, 
			event.mouseMove.y - position.y);
			setPosition(event.mouseMove.x, event.mouseMove.y);
			mActionBinding[ViewMove].category = Category::View;
			mActionBinding[ViewMove].action	 = derivedAction<ViewNode>(ViewMover(movement));
			commands.push(mActionBinding[ViewMove]);
		}		
	}
	else if(event.type == sf::Event::MouseButtonReleased){
		if (event.mouseButton.button == sf::Mouse::Left)
   		{
        	setPosition(0, 0);
    	}
	}
	else if(event.type == sf::Event::MouseButtonPressed){
		//sf::Vector2f mousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*(context.window));

		// conversion en coordonnées "monde"
		sf::Vector2f mouseOnSpace = context.window->mapPixelToCoords(mousePosition);

		mActionBinding[PlanetDisplay].category = Category::View;
		mActionBinding[PlanetDisplay].action = 
			derivedAction<ViewNode>(PlanetDisplayIntels(mouseOnSpace, true));
		commands.push(mActionBinding[PlanetDisplay]);
	}
	else if(event.type == sf::Event::MouseMoved){
		//sf::Vector2f mousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*(context.window));
	
		// conversion en coordonnées "monde"
		sf::Vector2f mouseOnSpace = context.window->mapPixelToCoords(mousePosition);

		mActionBinding[PlanetDisplay].category = Category::View;
		mActionBinding[PlanetDisplay].action = 
			derivedAction<ViewNode>(PlanetDisplayIntels(mouseOnSpace, false));
		commands.push(mActionBinding[PlanetDisplay]);
	}
}

void Player::setPosition(int x, int y){
	position = sf::Vector2f(x, y);
}
