#pragma once

#include "../Headers/fleet.hpp"
#include "../Headers/ship.hpp"
#include "../Headers/planet.hpp"
#include "../Headers/cursor.hpp"

class FleetHandler : public SceneNode
{
	public : 
								FleetHandler();
		void 					loadTextures();
		void 					createFleet(sf::Vector2f position, int planetNumber);
		unsigned int 			getFleetId(unsigned int planetNumber);
		void					addShip(unsigned int planetNumber, 
									Ship::Type type, int number);
		void					launchFleet(unsigned int planetNumber);
		void 					directFleet(sf::Vector2f objective, unsigned int planetNumber);
		void 					setCursor(Cursor::State nState);
		virtual unsigned int 	getCategory() const;

	private :

		// planet/fleet
		std::vector<std::pair<unsigned int, unsigned int> > 		fleetOwner;
		static unsigned int 										increment;
		TextureHolder												mTextures;
		FontHolder													mFonts;

};