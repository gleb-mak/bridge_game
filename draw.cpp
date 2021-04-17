#include "engine.h"
#include <iostream>

void Engine::draw()
{
	window.clear(sf::Color(255, 255, 255));
	for (auto& balk : balks)
	{
		window.draw(balk.get_sprite());
		window.draw(balk.fasteners[0].get_sprite());
		window.draw(balk.fasteners[1].get_sprite());
	}
	for (auto& fastener : fasteners)
	{
		window.draw(fastener.get_sprite());
	}
	window.draw(text);
	window.display();
}

