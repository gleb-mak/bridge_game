#include "balk.h"
#include <cmath>

#define G 0.001

Balk::Balk()
{
    len = 100;
    angle = 20;
	mass = 1;
	speed = 0;
	omega = 0;
	is_move = false;
	is_rotate = false;
	is_fixed = false;
	is_select = false;
    texture.loadFromFile("./images/stick.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 100));
	sprite.setRotation(angle);
	sprite.setOrigin(sf::Vector2f(5, 50));
	position = {100, 100};
    sprite.setPosition(position);
	fasteners.resize(2);
	// fasteners[0].initialize(get_begin(), "fastener.png");
	// fasteners[1].initialize(get_end(), "fastener.png");
	// fasteners[0].get_sprite().setPosition(sf::Vector2f(10, 10));
	// fasteners[1].get_sprite().setPosition(sf::Vector2f(110, 110));
//	fasteners[0].get_sprite().setPosition(get_begin());
//	fasteners[1].get_sprite().setPosition(get_end());
}

void Balk::initialize(float position_x, float position_y, int len_, double angle_, double mass_, string file)
{
    position.x = position_x;
	position.y = position_y;
    len = len_;
    angle = angle_;
    mass = mass_;
    texture.loadFromFile("./images/" + file);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, len));
//	sprite.setOrigin(sf::Vector2f(5, len / 2));
    sprite.setPosition(position);
    fasteners[0].initialize(get_begin(), "fastener.png");
    fasteners[1].initialize(get_end(), "fastener.png");
    //fasteners[0].get_sprite().setPosition(sf::Vector2f(300, 300));
    // fasteners[1].get_sprite().setPosition(get_end());
}

void Balk::setPosition_(sf::Vector2f new_pos)
{
	position = new_pos;
	sprite.setPosition(new_pos);
    fasteners[0].setPosition_(get_begin());
    fasteners[1].setPosition_(get_end());
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
    sf::Vector2f left_up_corner_to_begin = get_global_origin(sf::Vector2f(5, 100));
    sf::Vector2f global_origin = get_global_origin(sprite.getOrigin());
	sf::Vector2f ans = sprite.getPosition() - global_origin + left_up_corner_to_begin;
    return ans;
}

void Balk::update(float x, float y)
{
	if (is_move && !is_fixed)
	{
		position.x = x;
		position.y = y;
		setPosition_(position);
		//sprite.setPosition_(position);
	}
}

void Balk::update(float dt)
{
	if (is_rotate)
	{
		sprite.rotate(dt * 0.1);
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
}

void Balk::update(sf::Vector2f fix_pos)
{
	if (is_fixed)
	{
		ch_origin(sf::Vector2f(5, 0));
		sf::Vector2f delta = fix_pos - position;
		setPosition_(position + delta);
	}
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
		else if (M_PI / 2 < angle <= M_PI)
		{
			angle -= M_PI / 2;
			sign = -1;
		}
		else if (M_PI < angle <= 1.5 * M_PI)
		{
			angle = 1.5 * M_PI - angle;
		}
		else
		{
			angle =- 1.5 * M_PI;
		}
		omega += sign * 1.5 * G * cos(angle) * dt;
		sprite.rotate(omega * dt);
	}
	else
	{
		speed += dt * G;
		position.y += dt * speed;
		setPosition_(position);
	}
}

sf::Sprite Balk::get_sprite()
{
	return sprite;
}
