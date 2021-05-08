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
	for (auto& arrow : arrows)
	{
		if (arrow.is_valid)
			window.draw(arrow.get_sprite());
	}
	window.draw(text);
	window.draw(body.get_sprite());
	window.display();
}

