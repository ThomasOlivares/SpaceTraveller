#include "../Headers/world.hpp"
#include "../Headers/utility.hpp"
#include "../Headers/viewNode.hpp"
#include "../Headers/fleetHandler.hpp"

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
, mWorldBounds(-10000.f, -10000.f, 20000.f, 20000.f)
{
	mSceneTexture.create(mTarget.getSize().x, mTarget.getSize().y);

	loadTextures();
	buildScene();
}

void World::loadTextures()
{
	mTextures.load(Textures::Buttons,		"Media/Textures/Buttons.png");
	mTextures.load(Textures::Space, "Media/Textures/Space.png");
	mTextures.load(Textures::Planets, "Media/Textures/Planets.png");
	mTextures.load(Textures::Ships, "Media/Textures/Ships.png");
	mTextures.load(Textures::Cursor, "Media/Textures/Cible.png");
	mTextures.load(Textures::Symbol, "Media/Textures/cross.png");
}

void World::update(sf::Time dt)
{
	while (!mCommandQueue.isEmpty()){
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}

	mSceneGraph.update(dt, mCommandQueue);
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

	std::unique_ptr<ViewNode> viewNode(new ViewNode(mWorldView, mTarget));
	mSceneLayers[Background]->attachChild(std::move(viewNode));

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> spaceSprite(new SpriteNode(spaceBackground, textureRect));
	spaceSprite->setPosition(mWorldBounds.left, mWorldBounds.top - viewHeight);
	mSceneLayers[Background]->attachChild(std::move(spaceSprite));

	// Add the fleet handler
	std::unique_ptr<FleetHandler> handler(new FleetHandler());
	mSceneLayers[UpperAir]->attachChild(std::move(handler));

	addPlanets();
}

void World::addPlanets(){

	addPlanet(Planet::Blue, 0, 100, 100);
	addPlanet(Planet::Green, 1, 100, 600);
	addPlanet(Planet::Red, 2, 600, 100);
	addPlanet(Planet::Brown, 3, 600, 600);
}

void World::addPlanet(Planet::Type id, int number, int x, int y){
	std::unique_ptr<Planet> planet(new Planet(id, number, mTextures, mFonts, x, y));
	mSceneLayers[LowerAir]->attachChild(std::move(planet));
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}
