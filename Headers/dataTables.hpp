#pragma once

#include "../Headers/resourceIdentifiers.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>

class Planet;
class Ship;
class Button;

struct PlanetData
{
	int 							temperature;
	int 							size;
	Textures::ID					texture;
	sf::IntRect						textureRect;
};

struct ShipData
{
	Textures::ID					texture;
	sf::IntRect						textureRect;
	float							velocity;
};

struct CursorData
{
	Textures::ID					texture;
};

struct SymbolData
{
	Textures::ID					texture;
};

std::vector<PlanetData> initializePlanetData();
std::vector<ShipData> 	initializeShipData();
std::vector<CursorData> initializeCursorData();
std::vector<SymbolData> initializeSymbolData();