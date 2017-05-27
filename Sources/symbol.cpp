#include "../Headers/symbol.hpp"
#include "../Headers/category.hpp"
#include "../Headers/dataTables.hpp"
#include "../Headers/utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream>

namespace
{
	const std::vector<SymbolData> Table = initializeSymbolData();
}

Symbol::Symbol(sf::Vector2f location, Type type_, const TextureHolder& textures)
: mSprite(textures.get(Table[type_].texture))
, type(type_)
{
	centerOrigin(mSprite);
	setPosition(location);
	mSprite.scale(sf::Vector2f(0.2f, 0.2f));
}

void Symbol::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, states);
}

unsigned int Symbol::getCategory() const
{
	return Category::Symbol;
}
