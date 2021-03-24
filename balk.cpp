#include "balk.h"

Balk::Balk()
{
	position = {100, 100};
    len = 100;
    angle = 20;
	mass = 1;
	is_move = false;
	is_rotate = false;
    texture.loadFromFile("./images/stick.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 100));
	sprite.setRotation(angle);
	sprite.setOrigin(sf::Vector2f(5, 50));
    sprite.setPosition(position);
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
	sprite.setOrigin(sf::Vector2f(5, len / 2));
    sprite.setPosition(position);
}

void Balk::update(float x, float y)
{
	if (is_move)
	{
		position.x = x;
		position.y = y;
		sprite.setPosition(position);
	}
}

void Balk::update(double angle_)
{
	if (is_rotate)
	{
		sprite.rotate(angle_);
	}
}

sf::Sprite Balk::get_sprite()
{
	return sprite;
}
