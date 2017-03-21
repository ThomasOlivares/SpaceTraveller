#include "../Headers/world.hpp"
#include "../Headers/utility.hpp"

#include <algorithm>
#include <cmath>
#include <limits>


World::World(sf::RenderTarget& outputTarget, FontHolder& fonts)
: mTarget(outputTarget)
, mSceneTexture()
, mWorldView(outputTarget.getDefaultView())
, mTextures() 
, mFonts(fonts)
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 5000.f)
{
	mSceneTexture.create(mTarget.getSize().x, mTarget.getSize().y);

	loadTextures();
	buildScene();
}

void World::loadTextures()
{
	mTextures.load(Textures::Space, "Media/Textures/Space.png");
}

void World::update(sf::Time dt)
{

}

void World::draw()
{
	mTarget.setView(mWorldView);
	mTarget.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		Category::Type category = (i == LowerAir) ? Category::SceneAirLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& spaceBackground = mTextures.get(Textures::Space);
	spaceBackground.setRepeated(true);

	float viewHeight = mWorldView.getSize().y;
	sf::IntRect textureRect(mWorldBounds);
	textureRect.height += static_cast<int>(viewHeight);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> spaceSprite(new SpriteNode(spaceBackground, textureRect));
	spaceSprite->setPosition(mWorldBounds.left, mWorldBounds.top - viewHeight);
	mSceneLayers[Background]->attachChild(std::move(spaceSprite));
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}
