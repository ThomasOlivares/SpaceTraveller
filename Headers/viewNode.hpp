#pragma once

#include "../Headers/sceneNode.hpp"
#include "../Headers/commandQueue.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

class ViewNode : public SceneNode{

	public	:
								ViewNode(const sf::View &initialView, 
								 sf::RenderTarget& window_); 

		void 					zoomView(const float factor);
		virtual void 			updateCurrent(sf::Time, CommandQueue& commands);
		virtual void 			drawCurrent(sf::RenderTarget& target, 
									const sf::RenderStates states) const;
		virtual unsigned int 	getCategory() const;
		void 					moveView(sf::Vector2f movement);
		void 					handleEvent(sf::Vector2f mousePosition, 
									bool clicked);

	private :
		bool 			newCommand;
		Command 		displayPlanets;
		Command 		displayCursor;
		sf::View 		mView;
		float 			zoom;
		sf::Vector2f	mouseOnSpace;
		sf::Vector2f	mouseOnScreen;
		sf::RenderTarget&	window;
};
