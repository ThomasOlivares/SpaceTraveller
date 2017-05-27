#include "../Headers/cursor.hpp"
#include "../Headers/category.hpp"
#include "../Headers/dataTables.hpp"
#include "../Headers/utility.hpp"

#include <SFML/Window/Mouse.hpp>

namespace
{
	const std::vector<CursorData> Table = initializeCursorData();
}

Cursor::Cursor(const TextureHolder& textures)
: SceneNode()
, mSprite(textures.get(Table[State::Trigger].texture))
{
	setVisible(false);
	centerOrigin(mSprite);
}

void Cursor::changeState(State nState){
	if (nState == State::None){
		setVisible(false);
	}
	else{
		setVisible(true);
	}
}

void Cursor::select(sf::Vector2f mousePosition, bool clicked){
	setPosition(mousePosition);
}

void Cursor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (visible){
		target.draw(mSprite, states);
	}
}

unsigned int Cursor::getCategory() const{
	return Category::Cursor;
}