#include "../Headers/planet.hpp"
#include "../Headers/dataTables.hpp"
#include "../Headers/fleetHandler.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

struct FleetCreator
{
	FleetCreator(sf::Vector2f position_, int idPlanet_)
	: position(position_)
	, idPlanet(idPlanet_)
	{
	}

	void operator() (FleetHandler& fleetHandler, sf::Time) const{
		fleetHandler.createFleet(position, idPlanet);
	}

	sf::Vector2f 	position;
	int 			idPlanet;
};

struct FleetAdder
{
	FleetAdder(unsigned int planetNumber_, Ship::Type type_, int number_)
	: planetNumber(planetNumber_)
	, type(type_)
	, number(number_)
	{
	}

	void operator() (FleetHandler& fleetHandler, sf::Time) const{
		fleetHandler.addShip(planetNumber, type, number);
	}

	unsigned int 	planetNumber;
	Ship::Type 		type;
	int 			number;
};

struct FleetDirector
{
	FleetDirector(sf::Vector2f objective_, int planetNumber_)
	: objective(objective_)
	, planetNumber(planetNumber_)
	{
	}

	void operator() (FleetHandler& fleetHandler, sf::Time) const{
		fleetHandler.directFleet(objective, planetNumber);
	}

	sf::Vector2f 	objective;
	int 			planetNumber;
};

struct FleetSender
{
	FleetSender(unsigned int planetNumber_)
	: planetNumber(planetNumber_)
	{
	}

	void operator() (FleetHandler& fleetHandler, sf::Time) const{
		fleetHandler.launchFleet(planetNumber);
	}

	unsigned int 	planetNumber;
};

namespace
{
	const std::vector<PlanetData> Table = initializePlanetData();
}

Planet::Planet(Type type, int id_, const TextureHolder& textures, 
	const FontHolder& fonts, int x, int y)
: Entity(x, y)
, type(type)
, id(id_)
, temperature(Table[type].temperature)
, size(Table[type].size)
, isSelected(false)
{
	mSprite = sf::Sprite(textures.get(Table[type].texture), Table[type].textureRect);

	centerOrigin(mSprite);
	hitBox = Circle(getOrigin() + getPosition(), size);

	addShipTextures(textures, fonts);

	initializeButtons(textures, fonts);

	changeState(State::Home);
}

void Planet::addShipTextures(const TextureHolder& textures, const FontHolder& fonts){

	for (int index = 0; index < Ship::TypeCount; index++){
		Ship::Type type = static_cast<Ship::Type>(index);
		std::unique_ptr<Ship> ship(new Ship(type, textures, fonts));
		attachChild(std::move(ship));
	}
}

void Planet::initializeButtons(const TextureHolder& textures, const FontHolder& fonts){
	initializeButtonsHome(textures, fonts);
	initializeButtonsFleet(textures, fonts);
}

void Planet::initializeButtonsHome(const TextureHolder& textures, 
		const FontHolder& fonts)
{
	for (auto itr = mChildren.begin(); itr != mChildren.end(); itr++){
		auto& ship = static_cast<Ship&>(**itr);

		auto addButton = std::make_shared<GUI::Button>(textures, fonts);
		addButton->setPosition(ship.getPosition() + getPosition());
		addButton->setText("Add ship");
		addButton->setCallback([&] ()
		{
			addShip(ship.getType());
		});

		containers[State::Home].pack(addButton);
	}

	auto sendFleet = std::make_shared<GUI::Button>(textures, fonts);
	sendFleet->setPosition(getPosition() + sf::Vector2f(-50, 150));
	sendFleet->setText("Constitute fleet");
	sendFleet->setCallback([&] ()
	{
		addNewFleet();
		changeState(State::FleetBuild);
	});

	containers[State::Home].pack(sendFleet);
}

void Planet::addNewFleet(){
	Command createCommand;
	createCommand.category = Category::FleetHandler;
	createCommand.action = derivedAction<FleetHandler>(FleetCreator(
		getPosition(), getId()));
	fleetCommands.push_back(createCommand);
}

void Planet::initializeButtonsFleet(const TextureHolder& textures, 
		const FontHolder& fonts)
{
	for (auto itr = mChildren.begin(); itr != mChildren.end(); itr++){
		auto& ship = static_cast<Ship&>(**itr);

		auto addButton = std::make_shared<GUI::Button>(textures, fonts);
		addButton->setPosition(ship.getPosition() + getPosition());
		addButton->setText("Add ship to fleet");
		addButton->setCallback([&] ()
		{
			addShipFleet(ship.getType(), 1);
		});

		containers[FleetBuild].pack(addButton);
	}

	auto sendFleet = std::make_shared<GUI::Button>(textures, fonts);
	sendFleet->setPosition(getPosition() + sf::Vector2f(-50, 150));
	sendFleet->setText("Send fleet");
	sendFleet->setCallback([&] ()
	{
		changeState(State::FleetSend);
	});

	containers[FleetBuild].pack(sendFleet);
}

void Planet::addShipFleet(Ship::Type type, int number){
	Command addShipCommand;
	addShipCommand.category = Category::FleetHandler;
	addShipCommand.action = derivedAction<FleetHandler>(FleetAdder(
		getId(), type, number));
	fleetCommands.push_back(addShipCommand);
}

void Planet::launchFleet(){
	Command senderCommand;
	senderCommand.category = Category::FleetHandler;
	senderCommand.action = derivedAction<FleetHandler>(FleetSender(getId()));
	fleetCommands.push_back(senderCommand);
}

int Planet::getTemperature(){
	return temperature;
}

int Planet::getSize(){
	return size;
}

void Planet::addShip(Ship::Type type){
	int index = (int)type;
	auto& ship = static_cast<Ship&>(*(mChildren[index]));
	ship.add();
}

void Planet::updateCurrent(sf::Time, CommandQueue& commands)
{
	while (!fleetCommands.empty()){
		Command command = fleetCommands[fleetCommands.size() - 1];
		fleetCommands.pop_back();
		commands.push(command);
	}
	if(currentState!=State::FleetSend){
		currentContainer = &(containers[currentState]);
	}
}

void Planet::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
	if (isSelected && currentContainer != nullptr){
		target.draw(*currentContainer);
	}
}

void Planet::setShipVisible(bool visible){
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr){
		auto& node = static_cast<SceneNode&>(**itr);
		if (node.getCategory() == Category::Ship){
			auto& ship = static_cast<Ship&>(**itr);
			ship.setVisible(visible);
		}
	}
}

void Planet::select(sf::Vector2f mousePosition, bool clicked){
	if(currentState == State::FleetSend){
		if (clicked){
			sendFleet(mousePosition);
		}
		else{
			directFleet(mousePosition);
		}
	}
	else{
		if (hitBox.contain(mousePosition)){
			setShipVisible(true);
			isSelected = true;
			containers[currentState].select();
			containers[currentState].selectAt(mousePosition);
			if (clicked){
				containers[currentState].click();
			}
		}
		else{
			setShipVisible(false);
			isSelected = false;
			containers[currentState].deselect();
		}
	}
}

void Planet::sendFleet(sf::Vector2f objective){
	launchFleet();
	changeState(State::Home);
}

void Planet::directFleet(sf::Vector2f objective){
	Command directCommand;
	directCommand.category = Category::FleetHandler;
	directCommand.action = derivedAction<FleetHandler>(FleetDirector(objective, 
		getId()));
	fleetCommands.push_back(directCommand);
}

void Planet::changeState(State state){
	if (state == State::FleetSend){
		setShipVisible(false);
		currentContainer = nullptr;
	}
	currentState = state;
}

unsigned int Planet::getCategory() const
{
	return Category::Planet;
}

int Planet::getId() const
{
	return id;
}
