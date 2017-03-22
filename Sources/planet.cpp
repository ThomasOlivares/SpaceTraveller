#include "../Headers/planet.hpp"
#include "../Headers/dataTables.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace
{
	const std::vector<PlanetData> Table = initializePlanetData();
}

Planet::Planet(Type type, const TextureHolder& textures, int x, int y)
: Entity(x, y)
, temperature(Table[type].temperature)
, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
, size(Table[type].size)
{

}

int Planet::getTemperature(){
	return temperature;
}

int Planet::getSize(){
	return size;
}

void Planet::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}