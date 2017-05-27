#include "../Headers/fleet.hpp"
#include "../Headers/utility.hpp"
#include "../Headers/dataTables.hpp"
#include "../Headers/commandQueue.hpp"
#include "../Headers/symbol.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
#include <cmath>

#include "../Headers/cursor.hpp"

namespace
{
	const std::vector<ShipData> Table = initializeShipData();
}

Fleet::Fleet(int posX, int posY, unsigned int id_, const TextureHolder& textures, 
	const FontHolder& fonts)
: Entity(posX, posY)
, absoluteVelocityFleet(0)
, id(id_)
, objective(sf::Vector2f(0, 0))
{
	setVisible(false);
	setReverse(true);
	initShips(textures, fonts);
	initObjective(textures);
}

Fleet::Fleet(sf::Vector2f position, unsigned int id_, const TextureHolder& textures, 
	const FontHolder& fonts)
: Entity(position)
, absoluteVelocityFleet(0)
, id(id_)
, objective(sf::Vector2f(0, 0))
{
	setVisible(false);
	setReverse(true);
	initShips(textures, fonts);
	initObjective(textures);
}

void Fleet::initShips(const TextureHolder& textures, const FontHolder& fonts){
	for (int index = 0; index < Ship::TypeCount; index++){
		Ship::Type type = static_cast<Ship::Type>(index);
		ships[type].setContent(type, textures, fonts);

		shipTextures[type] = textures.get(Table[type].texture);
	}
}

void Fleet::initObjective(const TextureHolder& textures){
	std::unique_ptr<Symbol> symbol(new Symbol(objective - getPosition(), Symbol::Cross, 
		textures));
	symbol->setVisible(false);
	attachChild(std::move(symbol));
}

void Fleet::updateCurrent(sf::Time time, CommandQueue& commands){
	sf::Vector2f direction = unitVector(objective - getPosition());
	float rotation = toDegree(atan2(direction.y, direction.x));
	setRotation(rotation);
	setObjective(objective);

	Entity::updateCurrent(time, commands);
	if (distance(getPosition(), objective) < 1){
		stop();
	}
}

void Fleet::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Fleet::addShip(Ship::Type type, int number){
	changeTexture(type);
	changeVelocity(Table[type].velocity);
	ships[type].add(number);
}

// we take the texture of the bigger ship
void Fleet::changeTexture(Ship::Type type){
	for (int index = (int)type; index < Ship::TypeCount; index++){
		Ship::Type currentType = static_cast<Ship::Type>(index);
		if (ships[currentType].getNumber() != 0){
			return;
		}
	}
	mSprite = sf::Sprite(shipTextures[type], Table[type].textureRect);
	mSprite.scale(sf::Vector2f(0.2f, 0.2f));
	centerOrigin(mSprite);
}

// we take the velocity of the slowest ship
void Fleet::changeVelocity(float newVelocity){
	if (absoluteVelocityFleet == 0){
		absoluteVelocityFleet = newVelocity;
	}
	else{
		absoluteVelocityFleet = min(absoluteVelocityFleet, newVelocity);
	}
}

// once a fleet is send, we set all the number of ships to 0
void Fleet::reset(){
	setVisible(false);
	for (int index = 0; index < Ship::TypeCount; index++){
		Ship::Type type = static_cast<Ship::Type>(index);
		ships[type].reset();
	}
}

void Fleet::go(){
	absoluteVelocity = absoluteVelocityFleet;
	auto& cross = static_cast<Symbol&>(**(mChildren.begin()));
	cross.setVisible(true);
}

void Fleet::stop(){
	absoluteVelocity = 0;
}

void Fleet::setRotation(float angle){
	velocity.x = cos(toRadian(angle));
	velocity.y = sin(toRadian(angle));
	mSprite.setRotation(angle);
}

void Fleet::setObjective(sf::Vector2f objective_){
	objective = objective_;
	auto& cross = static_cast<Symbol&>(**(mChildren.begin()));
	cross.setPosition(objective - getPosition());
}

unsigned int Fleet::getCategory() const
{
	return Category::Fleet;
}

unsigned int Fleet::getId() const
{
	return id;
}