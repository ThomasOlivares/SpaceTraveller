#include "../Headers/ship.hpp"
#include "../Headers/dataTables.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream>

namespace
{
	const std::vector<ShipData> Table = initializeShipData();
}

Ship::Ship()
: number(0)
{
	setVisible(false);
}

Ship::Ship(Type type_, const TextureHolder& textures, const FontHolder& fonts)
: type(type_)
, number(0)
, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
{
	centerOrigin(mSprite);
	setVisible(false);

	adaptPosition();

	addTextNode(fonts);
}

void Ship::adaptPosition(){
	move(sf::Vector2f(-50, -50));
	switch(type){
		case XWing:
			move(sf::Vector2f(0, -100));
			break;
		case DeathStar:
			move(sf::Vector2f(0, 100));
			break;
		default:
			break;
	}

	mSprite.scale(sf::Vector2f(0.2f, 0.2f));
}

void Ship::addTextNode(const FontHolder& fonts){
	std::unique_ptr<TextNode> numberShips(new TextNode(fonts, ""));
	text = numberShips.get();
	attachChild(std::move(numberShips));
}

void Ship::add(){
	number++;
}

void Ship::add(int numberNewShips){
	number += numberNewShips;
}

void Ship::reset(){
	number = 0;
}

int Ship::getNumber(){
	return number;
}

Ship::Type Ship::getType(){
	return type;
}

void Ship::setContent(Type type_, const TextureHolder& textures, const FontHolder& fonts){
	type = type_;
	mSprite.setTexture(textures.get(Table[type].texture));
	mSprite.setTextureRect(Table[type].textureRect);

	centerOrigin(mSprite);
	setVisible(false);

	adaptPosition();

	addTextNode(fonts);
}

void Ship::updateCurrent(sf::Time, CommandQueue&)
{
	text->setString(toString(number));
}

void Ship::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Ship::getCategory() const
{
	return Category::Ship;
}
