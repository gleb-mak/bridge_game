#include "engine.h"

void Engine::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		window.close();
	}
}	
