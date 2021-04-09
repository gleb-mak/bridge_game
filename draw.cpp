#include "engine.h"

void Engine::draw_balk(Balk& balk)
{
	window.draw(balk.get_sprite());
	window.draw(balk.fasteners[0].get_sprite());
	window.draw(balk.fasteners[1].get_sprite());
}

void Engine::draw()
{
	window.clear(sf::Color(255, 255, 255));
	for (auto& balk : balks)
	{
		draw_balk(balk);
	}
	for (auto& fastener : fasteners)
	{
		window.draw(fastener.get_sprite());
	}
	window.display();
}

