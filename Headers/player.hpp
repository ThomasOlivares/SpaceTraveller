#pragma once

#include "../Headers/commandQueue.hpp"
#include "../Headers/state.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

#include <map>

class Player : private sf::NonCopyable{
	public:
		enum Action
		{
			Zoom, 
			ViewMove, 
			PlanetDisplay
		};

	public:
								Player();

		void					handleEvent(const sf::Event& event, 
			CommandQueue& commands, State::Context context);
		void 					setPosition(int x, int y);


	private:
		std::map<Action, Command>		mActionBinding;
		sf::Vector2f					position;
};