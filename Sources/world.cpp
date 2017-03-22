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
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
{
	mSceneTexture.create(mTarget.getSize().x, mTarget.getSize().y);

	zoomView(3);

	loadTextures();
	buildScene();
}

void World::loadTextures()
{
	mTextures.load(Textures::Space, "Media/Textures/Space.png");
	mTextures.load(Textures::Planets, "Media/Textures/Planets.png");
}

void World::update(sf::Time dt)
{

}

void World::zoomView(float factor){
	mWorldView.zoom(factor);
	mWorldBounds.left  = mWorldView.getCenter().x - mWorldView.getSize().x/2;
	mWorldBounds.top = mWorldView.getCenter().y - mWorldView.getSize().y/2;
	mWorldBounds.width = mWorldView.getSize().x;
	mWorldBounds.height = mWorldView.getSize().y;
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

	addPlanets();
}

void World::addPlanets(){

	addPlanet(Planet::Blue, 100, 100);
	addPlanet(Planet::Green, 100, 600);
	addPlanet(Planet::Red, 600, 100);
	addPlanet(Planet::Brown, 600, 600);
}

void World::addPlanet(Planet::Type id, int x, int y){
	std::unique_ptr<Planet> planet(new Planet(id, mTextures, x, y));
	mSceneLayers[LowerAir]->attachChild(std::move(planet));
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}
