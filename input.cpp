#include "engine.h"

void Engine::input()
{
	sf::Event event;
    while (window.pollEvent(event))
	{
		switch (event.type)
		{
        case sf::Event::Closed:
			window.close();
            break;
        case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Q:
					window.close();
					break;
				case sf::Keyboard::N:
					add_balk();
					break;
				case sf::Keyboard::G:
					is_gravity = !is_gravity;
					break;
				case sf::Keyboard::D:
					is_delete = true;
					break;
				default:
					break;
			}
            break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				is_right_pressed = true;
			}
			break;
		default:
            break;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		is_left_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		is_R_pressed = true;
	}
	else
	{
		is_R_pressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
    {
        is_L_pressed = true;
    }
}	
