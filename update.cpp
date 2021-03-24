#include "engine.h"

// sf::Vector2f& Vector2i_to_Vector2f(sf::Vector2i& v)
// {
//     return &sf::Vector2f((float)v.x, (float)v.y);
// }

void Engine::update(float sec)
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

				balk.is_rotate = true;
				balk.update(0.1);
				break;
			}
		}
	}
	is_left_pressed = false;
	is_right_pressed = false;
}

