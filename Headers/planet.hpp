#pragma once

#include "../Headers/entity.hpp"
#include "../Headers/resourceHolder.hpp"
#include "../Headers/resourceIdentifiers.hpp"
#include "../Headers/circle.hpp"
#include "../Headers/container.hpp"
#include "../Headers/button.hpp"
#include "../Headers/ship.hpp"
#include "../Headers/textNode.hpp"
#include "../Headers/command.hpp"
#include "../Headers/commandQueue.hpp"
#include "../Headers/fleet.hpp"

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

		enum State{
			Home, 
			FleetBuild,
			FleetSend
		};

	public : 
								Planet(Type type, int id_, const TextureHolder& textures, 
									const FontHolder& fonts, int x, int y);

		int 					getTemperature();
		int 					getSize();
		virtual void 			drawCurrent(sf::RenderTarget& target, 
									sf::RenderStates states) const;
		void 					updateCurrent(sf::Time, CommandQueue& commands);
		void 					addShipTextures(const TextureHolder& textures, 
									const FontHolder& fonts);
		void 					addShip(Ship::Type type);
		void 					initializeButtons(const TextureHolder& textures, 
									const FontHolder& fonts);
		void 					initializeButtonsHome(const TextureHolder& textures, 
									const FontHolder& fonts);
		void 					initializeButtonsFleet(const TextureHolder& textures, 
									const FontHolder& fonts);
		void 					addNewFleet();
		void 					addShipFleet(Ship::Type type, int number);
		void 					launchFleet();
		void 					select(sf::Vector2f mousePosition, bool clicked);
		void 					setShipVisible(bool visible);
		void 					directFleet(sf::Vector2f objective);
		void 					sendFleet(sf::Vector2f objective);
		void 					changeState(State id);
		virtual unsigned int 	getCategory() const;
		int 					getId() const;

	private :
		Type 								type;
		int    								id;
		int 								temperature;
		int 								size;

		bool 								isSelected;

		GUI::Container*						currentContainer;
		State								currentState;
		Circle 								hitBox;
		std::map<State, GUI::Container> 	containers;
		std::vector<Command>				fleetCommands;
};