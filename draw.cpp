#include "engine.h"

void Engine::draw()
{
	window.clear(sf::Color(255, 255, 255));
//  window.draw(balks.back().get_sprite());
	for (auto& balk : balks)
	{
		window.draw(balk.get_sprite());
	}
	window.display();
}
