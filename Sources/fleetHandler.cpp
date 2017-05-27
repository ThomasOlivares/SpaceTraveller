#include "../Headers/fleetHandler.hpp"
#include "../Headers/category.hpp"

#include <iostream>

unsigned int FleetHandler::increment = 0;

FleetHandler::FleetHandler()
: mTextures() 
, mFonts()
{
	loadTextures();
	std::unique_ptr<Cursor> cursor(new Cursor(mTextures));
	attachChild(std::move(cursor));
}

void FleetHandler::loadTextures()
{
	mTextures.load(Textures::Ships, "Media/Textures/Ships.png");
	mTextures.load(Textures::Cursor, "Media/Textures/Cible.png");
	mTextures.load(Textures::Symbol, "Media/Textures/cross.png");

	mFonts.load(Fonts::Main, 	"Media/Sansation.ttf");
}

void FleetHandler::createFleet(sf::Vector2f position, int planetNumber){
	fleetOwner.push_back(std::pair<unsigned int, unsigned int>(planetNumber, 
		increment));
	std::unique_ptr<Fleet> fleet(new Fleet(position, increment, mTextures, mFonts));
	attachChild(std::move(fleet));
	increment++;
}

void FleetHandler::addShip(unsigned int planetNumber, Ship::Type type, int number)
{
	unsigned int id = getFleetId(planetNumber);
	for (auto itr = ++mChildren.begin(); itr != mChildren.end(); ++itr){
		auto& fleet = static_cast<Fleet&>(**itr);
		if (fleet.getId() == id){
			fleet.addShip(type, number);
		}
	}
}

unsigned int FleetHandler::getFleetId(unsigned int planetNumber)
{
	//initialisation of the number of fleet found for this planet
	unsigned int numberFleet = -1;
	for (auto itr = fleetOwner.begin(); itr != fleetOwner.end(); ++itr){
		std::pair<unsigned int, int> pair = *itr;
		if(pair.first == planetNumber){
			numberFleet = pair.second;
		}
	}

	return numberFleet;
}

void FleetHandler::directFleet(sf::Vector2f objective, unsigned int planetNumber){
	unsigned int id = getFleetId(planetNumber);
	for (auto itr = ++mChildren.begin(); itr != mChildren.end(); ++itr){
		auto& fleet = static_cast<Fleet&>(**itr);
		if (fleet.getId() == id){
			fleet.setObjective(objective);
			fleet.setVisible(true);
		}
	}

	setCursor(Cursor::Trigger);
}

void FleetHandler::launchFleet(unsigned int planetNumber){
	unsigned int id = getFleetId(planetNumber);
	for (auto itr = ++mChildren.begin(); itr != mChildren.end(); ++itr){
		auto& fleet = static_cast<Fleet&>(**itr);
		if (fleet.getId() == id){
			fleet.go();
		}
	}
	setCursor(Cursor::None);
}

void FleetHandler::setCursor(Cursor::State nState){
	auto& cursor = static_cast<Cursor&>(**(mChildren.begin()));
	cursor.changeState(nState);
}

unsigned int FleetHandler::getCategory() const
{
	return Category::FleetHandler;
}