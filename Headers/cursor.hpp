#pragma once

#include "../Headers/resourceHolder.hpp"
#include "../Headers/resourceIdentifiers.hpp"
#include "../Headers/sceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class Cursor : public SceneNode
{
	public :
		enum State{
			None, 
			Trigger, 
			StateCount
		};
	public :
		Cursor(const TextureHolder& textures);
		void changeState(State nState);
		void select(sf::Vector2f mousePosition, bool clicked);

		virtual void 		drawCurrent(sf::RenderTarget& target, 
								sf::RenderStates states) const;
		virtual unsigned int getCategory() const;

	private :
		State state;
		sf::Sprite mSprite;
};