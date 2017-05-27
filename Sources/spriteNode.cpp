#include "../Headers/spriteNode.hpp"

using namespace std;

SpriteNode::SpriteNode(const sf::Texture& texture)
: mSprite(texture)
{
}	

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
: mSprite(texture, textureRect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int SpriteNode::getCategory() const
{
	return Category::Background;
}

void SpriteNode::setSize(int x, int y){
	sf::IntRect rect = mSprite.getTextureRect();
	rect.width = x;
	rect.height = y;
	mSprite.setTextureRect(rect);
}