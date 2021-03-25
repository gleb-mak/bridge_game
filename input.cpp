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
	//if (sf::Keyboard::isKeyPrssed(sf::Keyboard::R))
	{
		is_right_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		is_R_pressed = true;
	}
}	
