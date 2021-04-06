#include "balk.h"
#include <cmath>

#define G 0.001

Balk::Balk()
{
	fasteners.resize(2);
    len = 100;
    angle = 0;
	mass = 1;
	speed = 0;
	omega = 0;
	is_move = false;
	is_rotate = false;
	is_fixed = false;
	is_select = false;
	is_child = false;
	is_parent = false;
	is_len_inc = false;
	parent = NULL;
    texture.loadFromFile("./images/stick.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 100));
//	rotate_(angle);
	position = {100, 100};
    sprite.setPosition(position);
	fasteners[0].setPosition_(get_begin());
	fasteners[1].setPosition_(get_end());
	ch_origin(sf::Vector2f(5, 50));
	fasteners[0].setPosition_(position);
	fasteners[1].setPosition_(position);
}

void Balk::initialize(float position_x, float position_y, double len_, double angle_, double mass_, string file)
{
    position.x = position_x;
	position.y = position_y;
    len = len_;
    angle = angle_;
    mass = mass_;
    texture.loadFromFile("./images/" + file);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, len));
    setPosition_(position);
	rotate_(angle);
}

void Balk::setPosition_(sf::Vector2f new_pos)
{
	position = new_pos;
	sprite.setPosition(new_pos);
	fasteners[0].setPosition_(new_pos);
	fasteners[1].setPosition_(new_pos);
}

sf::Vector2f global_to_local(sf::Vector2f v_global, float alpha)
{
	alpha = alpha * M_PI / 180;
	sf::Vector2f i_1;
	sf::Vector2f i_2;
	i_1.x = cos(alpha);
	i_1.y = - sin(alpha);
	i_2.x = sin(alpha);
	i_2.y = cos(alpha);
	return v_global.x * i_1 + v_global.y * i_2;
}

void Balk::rotate_(float angle)
{
	sprite.rotate(angle);
	fasteners[1].get_sprite().rotate(angle);
	fasteners[0].get_sprite().rotate(angle);
}

sf::Vector2f Balk::get_begin()
{
	sf::Vector2f left_up_corner_to_begin = get_global_origin(sf::Vector2f(5, 0));
	sf::Vector2f global_origin = get_global_origin(sprite.getOrigin());
	sf::Vector2f ans = sprite.getPosition() - global_origin + left_up_corner_to_begin;
	return ans;
}

sf::Vector2f Balk::get_end()
{
    sf::Vector2f left_up_corner_to_begin = get_global_origin(sf::Vector2f(5, len));
    sf::Vector2f global_origin = get_global_origin(sprite.getOrigin());
	sf::Vector2f ans = sprite.getPosition() - global_origin + left_up_corner_to_begin;
    return ans;
}

void Balk::update_move(sf::Vector2f pos)
{
	if (is_move && !is_fixed && !is_child)
	{
		position = pos;
		setPosition_(position);
		is_move = false;
	}
}

void Balk::update_rotate(float dt)
{
	if (is_rotate)
	{
		rotate_(dt * 0.1);
		is_rotate = false;
	}
}

sf::Vector2f Balk::get_global_origin(sf::Vector2f origin)
{
    float alpha = sprite.getRotation() * M_PI / 180;
    sf::Vector2f j_1;
    j_1.x = -sin(alpha - M_PI / 2);
    j_1.y = cos(alpha - M_PI / 2);
    sf::Vector2f j_2;
    j_2.x = -sin(alpha);
    j_2.y = cos(alpha);
    return origin.x * j_1 + origin.y * j_2;
}

void Balk::ch_origin(sf::Vector2f new_origin)
{
    sf::Vector2f global_origin = get_global_origin(sprite.getOrigin());
    sf::Vector2f global_new_origin = get_global_origin(new_origin);
    sf::Vector2f delta = global_origin - global_new_origin;
    sprite.setPosition(sprite.getPosition() - delta);
	position = sprite.getPosition();
    sprite.setOrigin(new_origin);
    sf::Vector2f origin_global_1 = sprite.getPosition() - fasteners[1].get_sprite().getPosition() + get_global_origin(fasteners[1].get_sprite().getOrigin());
    sf::Vector2f origin_global_0 = sprite.getPosition() - fasteners[0].get_sprite().getPosition() + get_global_origin(fasteners[0].get_sprite().getOrigin());
    sf::Vector2f origin_local_1 = global_to_local(origin_global_1, fasteners[1].get_sprite().getRotation());
    sf::Vector2f origin_local_0 = global_to_local(origin_global_0, fasteners[0].get_sprite().getRotation());
    fasteners[1].ch_origin(origin_local_1);
    fasteners[0].ch_origin(origin_local_0);
}

void Balk::update_fix(sf::Vector2f fix_pos)
{
	if (is_fixed)
	{
		ch_origin(sf::Vector2f(5, 0));
		sf::Vector2f delta = fix_pos - position;
		setPosition_(position + delta);
	}
}

double Balk::example(double x)
{
	return x;
}

void Balk::update_gravity(float dt)
{
	if (is_fixed)
	{
		double angle = sprite.getRotation() * M_PI / 180;
		int sign = 1;
		if (angle <= M_PI / 2)
		{
			angle = M_PI / 2 - angle;
			sign = -1;
		}
		else if (M_PI / 2 < angle && angle <= M_PI)
		{
			angle -= M_PI / 2;
			sign = -1;
		}
		else if (M_PI < angle && angle <= 1.5 * M_PI)
		{
			angle = 1.5 * M_PI - angle;
		}
		else
		{
			angle =- 1.5 * M_PI;
		}
		omega += sign * 1.5 * G * sin(angle) * dt;
		rotate_(omega * dt);
	}
	else if (!is_child)
	{
		speed += dt * G;
		position.y += dt * speed;
		setPosition_(position);
	}
}

void Balk::update_become_child(Balk* p)
{
	if (is_child)
	{
		set_parent(p);
		ch_origin(sf::Vector2f(5, 0));
		setPosition_(parent->get_end());
	}
}

void Balk::update_child()
{
	if (is_child)
	{
		setPosition_(parent->get_end());
	}
}

sf::Sprite& Balk::get_sprite()
{
	return sprite;
}

void Balk::set_parent(Balk* b)
{
	parent = b;
	b->is_parent = true;
}

void Balk::update_len_inc()
{
	if (is_len_inc)
	{
		sprite.setTextureRect(sf::IntRect(0, 0, 10, len + 0.005));
		fasteners[1].ch_origin(sf::Vector2f(5, 5));
		fasteners[1].get_sprite().setPosition(get_end());
		sf::Vector2f origin_global_1 = sprite.getPosition() - fasteners[1].get_sprite().getPosition() + get_global_origin(fasteners[1].get_sprite().getOrigin());
		sf::Vector2f origin_local_1 = global_to_local(origin_global_1, fasteners[1].get_sprite().getRotation());
		fasteners[1].ch_origin(origin_local_1);
		len += 0.005;
		is_len_inc = false;
	}
}
