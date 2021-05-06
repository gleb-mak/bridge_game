#include "Runge.h"
#include "balk.h"
#include <cmath>

#define REZIST_MOMENTUM 0.003
#define G 0.001

Balk::Balk()
{
	fasteners.resize(2);
    len = 100;
    angle = 0;
	mass = 1;
	ro = mass / len;
	speed = 0;
	omega = 0;
	child_number = 0;
	is_move = false;
	is_rotate = false;
	is_fixed = false;
	is_end_fixed = false;
	is_select = false;
	is_child = false;
	is_parent = false;
	is_resize = false;
	is_in_fixed_chain = false;
	parent = NULL;
    texture.loadFromFile("./images/stick.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 100));
	position = {100, 100};
    sprite.setPosition(position);
	fasteners[0].setPosition_(get_begin());
	fasteners[1].setPosition_(get_end());
	ch_origin(sf::Vector2f(5, 50));
	fasteners[0].setPosition_(position);
	fasteners[1].setPosition_(position);
}

Balk::~Balk()
{
	fasteners.clear();
	if (is_child)
	{
		parent->child_number--;
		if (parent->child_number == 0)
		{
			parent->is_parent = false;
			parent->fasteners[1].ch_color("blue");
		}
	}
	if (is_end_fixed)
	{
		Balk* tmp = this;
		while (tmp != NULL)
        {
            tmp->is_in_fixed_chain = false;
            tmp = tmp->parent;
        }
	}
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

double Balk::get_mass()
{
	return mass;
}

double Balk::get_len()
{
	return len;
}

double Balk::get_omega()
{
	return omega;
}

void Balk::set_omega(double o)
{
	omega = o;
}

void Balk::setPosition_(sf::Vector2f new_pos)
{
	position = new_pos;
	sprite.setPosition(new_pos);
	fasteners[0].setPosition_(new_pos);
	fasteners[1].setPosition_(new_pos);
}

void Balk::rotate_(float angle)
{
	sprite.rotate(angle);
	fasteners[1].get_sprite().rotate(angle);
	fasteners[0].get_sprite().rotate(angle);
}

void Balk::setRotation_(float angle)
{
    sprite.setRotation(angle);
    fasteners[1].get_sprite().setRotation(angle);
    fasteners[0].get_sprite().setRotation(angle);
}

sf::Vector2f Balk::get_begin()
{
	sf::Vector2f left_up_corner_to_begin = get_global_origin(sf::Vector2f(5, 0), sprite);
	sf::Vector2f global_origin = get_global_origin(sprite.getOrigin(), sprite);
	sf::Vector2f ans = sprite.getPosition() - global_origin + left_up_corner_to_begin;
	return ans;
}

sf::Vector2f Balk::get_end()
{
    sf::Vector2f left_up_corner_to_begin = get_global_origin(sf::Vector2f(5, len), sprite);
    sf::Vector2f global_origin = get_global_origin(sprite.getOrigin(), sprite);
	sf::Vector2f ans = sprite.getPosition() - global_origin + left_up_corner_to_begin;
    return ans;
}

void Balk::update_move(sf::Vector2f pos)
{
	if (is_move && !is_fixed && !is_child && !is_in_fixed_chain)
	{
        if (sprite.getOrigin() != sf::Vector2f(5, len / 2))
        {
            ch_origin(sf::Vector2f(5, len / 2));
        }
		position = pos;
		setPosition_(position);
		is_move = false;
	}
}

void Balk::update_rotate(float dt)
{
	if (is_rotate && !is_in_fixed_chain)
	{
		rotate_(dt * 0.1);
		is_rotate = false;
	}
}

void Balk::ch_origin(sf::Vector2f new_origin)
{
    sf::Vector2f global_origin = get_global_origin(sprite.getOrigin(), sprite);
    sf::Vector2f global_new_origin = get_global_origin(new_origin, sprite);
    sf::Vector2f delta = global_origin - global_new_origin;
    sprite.setPosition(sprite.getPosition() - delta);
	position = sprite.getPosition();
    sprite.setOrigin(new_origin);
    sf::Vector2f origin_global_1 = sprite.getPosition() - fasteners[1].get_sprite().getPosition() + get_global_origin(fasteners[1].get_sprite().getOrigin(), sprite);
    sf::Vector2f origin_global_0 = sprite.getPosition() - fasteners[0].get_sprite().getPosition() + get_global_origin(fasteners[0].get_sprite().getOrigin(), sprite);
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
		fasteners[0].ch_color("green");
	}
}



double Balk::movement_ODE(double t, double angle, double c, double len, double mass)
{
	return ((3 * G * sin(angle))/(2*len))  -(c/((c == 0)? 1 : fabs(c) )) * (3 * REZIST_MOMENTUM) / (mass * len * len);
}

void Balk::update_gravity(double dt, double t)
{
	if (is_in_fixed_chain)
	{
		return;
	}
	if (is_fixed && !is_parent)
	{
		double angle = sprite.getRotation() * M_PI / 180;
		if (angle >= M_PI)
		{
			angle -= M_PI;
			angle = -angle;
		}
		// double y[5];
		// int number_of_steps = 4;
		// double h = dt;
		// y[0] = angle;
		// Runge_Kutta_2nd_Order(Balk::movement_ODE, 0, y, omega, h, number_of_steps, len, mass);
		// rotate_((y[0] - y[4]) * 180/M_PI);
		double new_angle = Runge_Kutta(angle, t, omega, dt, mass, G, len);
		rotate_((angle - new_angle) * 180/M_PI);
	}
	// else if (!is_child)
	// {
	// 	speed += dt * G;
	// 	position.y += dt * speed;
	// 	setPosition_(position);
	// }
}

void Balk::update_become_child(Balk* p)
{
	if (is_child)
	{
		set_parent(p);
		ch_origin(sf::Vector2f(5, 0));
		setPosition_(parent->get_end());
		fasteners[0].ch_color("green");
		parent->fasteners[1].ch_color("green");
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
	b->child_number++;
}

void Balk::set_len(double new_len)
{
	sprite.setTextureRect(sf::IntRect(0, 0, 10, new_len));
	fasteners[1].ch_origin(sf::Vector2f(5, 5));
	fasteners[1].get_sprite().setPosition(get_end());
	sf::Vector2f origin_global_1 = sprite.getPosition() - fasteners[1].get_sprite().getPosition() + get_global_origin(fasteners[1].get_sprite().getOrigin(), sprite);
	sf::Vector2f origin_local_1 = global_to_local(origin_global_1, fasteners[1].get_sprite().getRotation());
	fasteners[1].ch_origin(origin_local_1);
	len = new_len;
	mass = len * ro;
}

void Balk::update_size(sf::Vector2f mouse_pos)
{
	if (is_resize && !is_in_fixed_chain)
	{
		if (sprite.getOrigin() != sf::Vector2f(5, 0))
		{
			ch_origin(sf::Vector2f(5, 0));
		}
		sf::Vector2f begin_to_mouse = mouse_pos - get_begin();
		float angle = -atan2(begin_to_mouse.x, begin_to_mouse.y) * 180 / M_PI;
		setRotation_(angle);
		double new_len = vector_abs(sprite.getPosition() - mouse_pos);
		set_len(new_len);
	}
}

void Balk::update_end_fix(sf::Vector2f fix_pos)
{
	if (is_end_fixed)
	{
		sf::Vector2f direct = fix_pos - sprite.getPosition();
		double new_len = vector_abs(direct);
		set_len(new_len);
		float angle = -atan2(direct.x, direct.y) * 180 / M_PI;
		setRotation_(angle);
		fasteners[1].ch_color("green");
		Balk* tmp = this; 
		while (tmp != NULL)
		{
			tmp->is_in_fixed_chain = true;
			tmp = tmp->parent;
		}
	}
}

sf::Vector2f Balk::len_vector()
{
	return get_end() - get_begin();
}
