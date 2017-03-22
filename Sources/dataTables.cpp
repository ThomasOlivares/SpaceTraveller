#include "../Headers/dataTables.hpp"
#include "../Headers/planet.hpp"

std::vector<PlanetData> initializePlanetData()
{
	std::vector<PlanetData> data(Planet::TypeCount);

	data[Planet::Blue].temperature = 25;
	data[Planet::Blue].size = 150;
	data[Planet::Blue].texture = Textures::Planets;
	data[Planet::Blue].textureRect = sf::IntRect(0, 0, 600, 600);

	data[Planet::Green].temperature = 25;
	data[Planet::Green].size = 150;
	data[Planet::Green].texture = Textures::Planets;
	data[Planet::Green].textureRect = sf::IntRect(600, 0, 600, 600);

	data[Planet::Red].temperature = 25;
	data[Planet::Red].size = 150;
	data[Planet::Red].texture = Textures::Planets;
	data[Planet::Red].textureRect = sf::IntRect(1200, 0, 600, 600);

	data[Planet::Brown].temperature = 25;
	data[Planet::Brown].size = 150;
	data[Planet::Brown].texture = Textures::Planets;
	data[Planet::Brown].textureRect = sf::IntRect(1800, 0, 600, 600);

	return data;
}