#include "engine.h"

sf::Vector2f vector_i_to_f(sf::Vector2i v)
{
	return sf::Vector2f((float)v.x, (float)v.y);
}

void Engine::update(float dt)
{
	list<Balk>::iterator balk = balks.begin();
	while (balk != balks.end())
	{
		if (is_left_pressed)
		{
	        if (!balk->is_parent && balk->fasteners[1].get_sprite().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
				balk->is_resize = true;
				sf::Vector2f mouse_pos = vector_i_to_f(sf::Mouse::getPosition(window));
				balk->update_size(mouse_pos);
				break;
            }
			if (balk->get_sprite().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				balk->is_move = true;
				sf::Vector2f mouse_pos = vector_i_to_f(sf::Mouse::getPosition(window));
				balk->update_move(mouse_pos);
				break;
			}
		}
		if (is_right_pressed)
		{
			bool flag = false;
            if (balk->get_sprite().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && !flag)
			{
				balk->is_select = true;
				flag = true;
			}
			else
			{
				balk->is_select = false;
			}
		}
		if (balk->is_select)
		{
			if (is_R_pressed)
			{
				balk->is_rotate = true;
				balk->update_rotate(dt);
			}
			if (is_delete && !balk->is_parent)
			{
				if (balk->is_fixed)
				{
					fasteners[0].ch_color("blue");
				}
				if (balk->is_end_fixed)
				{
					fasteners[1].ch_color("blue");
				}
				balk = balks.erase(balk);
				break;
			}
		}
        if (!balk->is_fixed && !balk->is_child && balk->get_sprite().getGlobalBounds().contains(fasteners[0].get_sprite().getPosition()))
		{
			balk->is_fixed = true;
			balk->update_fix(fasteners[0].get_sprite().getPosition());
			fasteners[0].ch_color("green");
		}
		if (!balk->is_end_fixed && (balk->is_child || balk->is_fixed) && balk->fasteners[1].get_sprite().getGlobalBounds().contains(fasteners[1].get_sprite().getPosition()))
		{
			balk->is_end_fixed = true;
			fasteners[1].ch_color("green");
			balk->update_end_fix(fasteners[1].get_sprite().getPosition());
		}
		if (!balk->is_child && !balk->is_fixed)
		{
			list<Balk>::iterator it = balks.begin();
			for (auto& item : balks)
			{
				if ((item.is_fixed || item.is_child) && it != balk && balk->get_sprite().getGlobalBounds().intersects(item.fasteners[1].get_sprite().getGlobalBounds()))
				{
					balk->is_child = true;
					balk->update_become_child(&item);
					break;
				}
				it++;
			}
		}
		if (balk->is_child)
		{
			balk->update_child();			
		}
		if (is_gravity)
		{
			balk->update_gravity(dt);
		}
		balk++;
	}
    is_left_pressed = false;
    is_right_pressed = false;
	is_delete = false;
}

