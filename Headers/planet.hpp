#pragma once

#include "../Headers/entity.hpp"
#include "../Headers/resourceHolder.hpp"
#include "../Headers/resourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Planet : public Entity
{
	public :
		enum Type{
			Blue, 
			Green, 
			Red, 
			Brown, 
			TypeCount
		};

	public : 
							Planet(Type type, const TextureHolder& textures, int x, int y);

		int 				getTemperature();
		int 				getSize();
		virtual void 		drawCurrent(sf::RenderTarget& target, 
								sf::RenderStates states) const;

	private :
		int 				temperature;
		int 				size;
		sf::Sprite			mSprite;
};