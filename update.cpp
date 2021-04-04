#include "engine.h"

sf::Vector2f vector_i_to_f(sf::Vector2i v)
{
	return sf::Vector2f((float)v.x, (float)v.y);
}

void Engine::update(float dt)
{
	for (auto& balk : balks)
	{
		if (is_left_pressed)
		{
			if (balk.get_sprite().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				balk.is_move = true;
				sf::Vector2f mouse_pos = vector_i_to_f(sf::Mouse::getPosition(window));
				balk.update_move(mouse_pos);
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
			else
			{
				balk.is_select = false;
			}
		}
		if (is_R_pressed && balk.is_select)
		{
			balk.is_rotate = true;
			balk.update_rotate(dt);
			break;
		}
        if (!balk.is_fixed && balk.get_sprite().getGlobalBounds().contains(fastener.get_sprite().getPosition()))
		{
			balk.is_fixed = true;
			sf::Vector2f dist = fastener.get_sprite().getPosition() - balk.get_sprite().getPosition();
			balk.update_fix(fastener.get_sprite().getPosition());
		}
		if (balk.is_fixed)
		{
			for (auto& it : balks)
			{
				if (&it != &balk && balk.get_sprite().getGlobalBounds().contains(it.fasteners[0].get_sprite().getPosition()))
				{
					
				}
			}
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

