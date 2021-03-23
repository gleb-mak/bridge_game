#include "engine.h"

void Engine::draw()
{
	window.clear(sf::Color(255, 255, 255));
//	window.draw(balks.front().get_sprite());
	window.display();
}
