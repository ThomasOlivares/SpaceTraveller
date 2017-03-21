#ifndef WORLD_HPP
#define WORLD_HPP

#include "../Headers/resourceHolder.hpp"
#include "../Headers/resourceIdentifiers.hpp"
#include "../Headers/sceneNode.hpp"
#include "../Headers/spriteNode.hpp"
#include "../Headers/commandQueue.hpp"
#include "../Headers/command.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <array>
#include <queue>

class World : private sf::NonCopyable
{
	public:
											World(sf::RenderTarget& outputTarget, FontHolder& fonts);
		void								update(sf::Time dt);
		void								draw();

		sf::FloatRect						getViewBounds() const;		
		CommandQueue&						getCommandQueue();



	private:
		void								loadTextures();
		void								buildScene();


	private:
		enum Layer
		{
			Background,
			LowerAir,
			UpperAir,
			LayerCount
		};

	private:
		sf::RenderTarget&					mTarget;
		sf::RenderTexture					mSceneTexture;
		sf::View							mWorldView;
		TextureHolder						mTextures;
		FontHolder&							mFonts;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;

};

#endif // WORLD_HPP
