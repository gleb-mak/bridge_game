#include "engine.h"
#include <iostream>
#include <algorithm>

sf::Vector2f vector_i_to_f(sf::Vector2i v)
{
	return sf::Vector2f((float)v.x, (float)v.y);
}

void Engine::update(double dt)
{
	if (is_gravity)
	{
		g_time += dt;
	}
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
			if (body.get_sprite().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				body.update_move(fasteners[0].get_sprite().getPosition());
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
			add_chain(std::addressof(*balk));
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
					for (auto& chain : chains)
					{
						if (chain.get_balks().front() == &item)
						{
							if (!item.is_parent)
							{
								chain.add_balk(std::addressof(*balk));
							}
							break;
						}
					}
					// for (auto& chain : chains)
					// {
					// 	if (std::find(chain.get_balks().begin(), chain.get_balks().end(), &item) != chain.get_balks().end())
					// 	{
					// 		if (!item.is_parent)
					// 		{
					// 			chain.add_balk(std::addressof(*balk));
					// 		}
					// 		else
					// 		{
					// 			chains.push_back(chain.copy());
					// 			chains.back().add_balk(std::addressof(*balk));
					// 		}
					// 		break;
					// 	}
					// }
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
			balk->update_gravity(dt, g_time);
		}
		balk++;
	}
	for (auto& chain : chains)
	{
		if (is_gravity)
		{
			chain.update_gravity(dt, g_time);
		}
	}
    is_left_pressed = false;
    is_right_pressed = false;
	is_delete = false;
}

