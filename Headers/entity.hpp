#pragma once

#include "../Headers/sceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class Entity : public SceneNode
{
	public :
							Entity(int posX, int posY);
							Entity(sf::Vector2f position);

		void				setVelocity(sf::Vector2f velocity_);
		sf::Vector2f		getVelocity();

		virtual void 		updateCurrent(sf::Time time, CommandQueue&);

	protected :

		sf::Sprite			mSprite;
		sf::Vector2f		velocity;
		float				absoluteVelocity;

};
