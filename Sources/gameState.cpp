#include "../Headers/gameState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts)
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();

	return true;
}