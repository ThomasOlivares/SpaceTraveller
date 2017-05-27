#include "../Headers/dataTables.hpp"
#include "../Headers/planet.hpp"
#include "../Headers/ship.hpp"
#include "../Headers/button.hpp"
#include "../Headers/cursor.hpp"
#include "../Headers/symbol.hpp"

std::vector<PlanetData> initializePlanetData()
{
	std::vector<PlanetData> data(Planet::TypeCount);

	data[Planet::Blue].temperature = 25;
	data[Planet::Blue].size = 235;
	data[Planet::Blue].texture = Textures::Planets;
	data[Planet::Blue].textureRect = sf::IntRect(0, 0, 600, 600);

	data[Planet::Green].temperature = 25;
	data[Planet::Green].size = 235;
	data[Planet::Green].texture = Textures::Planets;
	data[Planet::Green].textureRect = sf::IntRect(600, 0, 600, 600);

	data[Planet::Red].temperature = 25;
	data[Planet::Red].size = 235;
	data[Planet::Red].texture = Textures::Planets;
	data[Planet::Red].textureRect = sf::IntRect(1200, 0, 600, 600);

	data[Planet::Brown].temperature = 25;
	data[Planet::Brown].size = 235;
	data[Planet::Brown].texture = Textures::Planets;
	data[Planet::Brown].textureRect = sf::IntRect(1800, 0, 600, 600);

	return data;
}

std::vector<ShipData> initializeShipData()
{
	std::vector<ShipData> data(Ship::TypeCount);

	data[Ship::XWing].texture = Textures::Ships;
	data[Ship::XWing].textureRect = sf::IntRect(0, 0, 600, 600);
	data[Ship::XWing].velocity = 50;

	data[Ship::Destroyer].texture = Textures::Ships;
	data[Ship::Destroyer].textureRect = sf::IntRect(600, 0, 600, 600);
	data[Ship::Destroyer].velocity = 10;

	data[Ship::DeathStar].texture = Textures::Ships;
	data[Ship::DeathStar].textureRect = sf::IntRect(1200, 0, 600, 600);
	data[Ship::DeathStar].velocity = 3;

	return data;
}

std::vector<CursorData> initializeCursorData()
{
	std::vector<CursorData> data(Cursor::StateCount);

	data[Cursor::None].texture = 	Textures::Cursor;
	data[Cursor::Trigger].texture = Textures::Cursor;

	return data;
}

std::vector<SymbolData> initializeSymbolData()
{
	std::vector<SymbolData> data(Symbol::TypeCount);

	data[Symbol::Cross].texture = Textures::Symbol;

	return data;
}