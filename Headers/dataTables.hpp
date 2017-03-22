#pragma once

#include "../Headers/resourceIdentifiers.hpp"
#include <SFML/Graphics/Rect.hpp>

class Planet;

struct PlanetData
{
	int 							temperature;
	int 							size;
	Textures::ID					texture;
	sf::IntRect						textureRect;
};

std::vector<PlanetData> initializePlanetData();