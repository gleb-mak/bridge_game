#include "engine.h"

void Engine::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		add_balk();		
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		is_left_pressed = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		is_right_pressed = true;
	}
}	
