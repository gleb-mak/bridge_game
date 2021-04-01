#include "engine.h"

void Engine::update(float dt)
{
//	if (sf::Keyboard::)
	for (auto& balk : balks)
	{
		if (is_left_pressed)
		{
			if (balk.get_sprite().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				balk.is_move = true;
				sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
				balk.update((float)mouse_pos.x, (float)mouse_pos.y);
				break;
			}
		}
		if (is_right_pressed)
		{
            if (balk.get_sprite().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				balk.is_select = true;
				break;
			}
		}
		if (is_R_pressed && balk.is_select)
		{
			balk.is_rotate = true;
			balk.update(dt);
			break;
		}
        if (balk.get_sprite().getGlobalBounds().contains(fastener.get_sprite().getPosition()))
		{
			balk.is_fixed = true;
			sf::Vector2f dist = fastener.get_sprite().getPosition() - balk.get_sprite().getPosition();
			balk.update(fastener.get_sprite().getPosition());
		}
		if (is_gravity)
		{
			balk.update_gravity(dt);
		}
	}
	is_left_pressed = false;
	is_right_pressed = false;
	is_R_pressed = false;
}

