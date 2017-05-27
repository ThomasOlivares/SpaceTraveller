#pragma once

#include "../Headers/ship.hpp"
#include "../Headers/entity.hpp"
#include "../Headers/resourceHolder.hpp"
#include "../Headers/resourceIdentifiers.hpp"

#include <SFML/System/Vector2.hpp>

class Fleet : public Entity
{
	public :
							Fleet(int posX, int posY, unsigned int id_, 
								const TextureHolder& textures, const FontHolder& fonts);
							Fleet(sf::Vector2f position, unsigned int id_, 
								const TextureHolder& textures, const FontHolder& fonts);

		virtual void 			updateCurrent(sf::Time, CommandQueue&);
		virtual void 			drawCurrent(sf::RenderTarget& target, 
									sf::RenderStates states) const;

		void 					initShips(const TextureHolder& textures, 
									const FontHolder& fonts);
		void					initObjective(const TextureHolder& textures);
		void 					addShip(Ship::Type type, int number);
		void 					changeTexture(Ship::Type type);
		void 					changeVelocity(float newVelocity);
		void 					setRotation(float angle);
		void					setObjective(sf::Vector2f objective);
		void 					reset();
		void 					go();
		void 					stop();
		virtual unsigned int 	getCategory() const;
		unsigned int 			getId() const;

	private :
		unsigned int 							id;
		float									absoluteVelocityFleet;
		std::map<Ship::Type, sf::Texture>		shipTextures;
		std::map<Ship::Type, Ship > 			ships;
		sf::Sprite 								mSprite;
		sf::Vector2f							objective;
};
