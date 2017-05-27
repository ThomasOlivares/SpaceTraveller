#pragma once

#include "../Headers/sceneNode.hpp"
#include "../Headers/resourceHolder.hpp"
#include "../Headers/resourceIdentifiers.hpp"
#include "../Headers/textNode.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Ship : public SceneNode{

	public :
		enum Type{
			XWing, 
			Destroyer, 
			DeathStar, 
			TypeCount
		};

	public :
							Ship();
							Ship(Type type, const TextureHolder& textures, 
								const FontHolder& fonts);

		virtual void 		updateCurrent(sf::Time, CommandQueue&);
		virtual void 		drawCurrent(sf::RenderTarget& target, 
								sf::RenderStates states) const;
		Ship::Type 			getType();
		void 				adaptPosition();
		void 				add();
		void 				add(int numberNewShips);
		void 				reset();
		int 				getNumber();
		void 				addTextNode(const FontHolder& fonts);
		void 				setContent(Type type_, const TextureHolder& textures, 
								const FontHolder& fonts);
		
		virtual unsigned int getCategory() const;

	private :
		Type 				type;
		sf::Sprite			mSprite;
		TextNode*			text;
		int 				number;
};
