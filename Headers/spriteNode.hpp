#ifndef SPRITE_NODE
#define SPRITE_NODE

#include "../Headers/sceneNode.hpp"

#include <SFML/Graphics.hpp>



class SpriteNode : public SceneNode{
	public:
		explicit 				SpriteNode(const sf::Texture& texture);
								SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
		void 					setSize(int x, int y);
		virtual unsigned int 	getCategory() const;

	private:
		virtual void 			drawCurrent(sf::RenderTarget& target, 
									sf::RenderStates states) const;

	private:
		sf::Sprite mSprite;
};

#endif //SPRITE_NODE