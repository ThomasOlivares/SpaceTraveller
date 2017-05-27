#pragma once

#include "../Headers/sceneNode.hpp"
#include "../Headers/resourceHolder.hpp"
#include "../Headers/resourceIdentifiers.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Symbol : public SceneNode
{
	public : 
		enum Type{
			Cross, 
			TypeCount
		};
	public :
		Symbol(sf::Vector2f location, Type type_, const TextureHolder& textures);

		virtual void 			drawCurrent(sf::RenderTarget& target, 
									sf::RenderStates states) const;

		virtual unsigned int getCategory() const;

	private :
		sf::Sprite mSprite;
		Type type;
};