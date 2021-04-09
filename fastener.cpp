#include "Runge.h"
#include "fastener.h"
#include <cmath>

Fastener::Fastener()
{
	position.x = 400;
	position.y = 400;
	texture.loadFromFile("./images/fastener.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setOrigin(sf::Vector2f(5, 5));
    sprite.setPosition(position);
}

void Fastener::initialize(sf::Vector2f pos, string file)
{
	position = pos;
	texture.loadFromFile("./images/" + file);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setPosition(position);
}

sf::Texture& Fastener::get_texture()
{
	return texture;
}

void Fastener::setPosition_(sf::Vector2f pos)
{
	position = pos;
	sprite.setPosition(pos);
}

sf::Sprite& Fastener::get_sprite()
{
	return sprite;
}

void Fastener::ch_origin(sf::Vector2f new_origin)
{
    sf::Vector2f global_origin = get_global_origin(sprite.getOrigin(), sprite);
    sf::Vector2f global_new_origin = get_global_origin(new_origin, sprite);
    sf::Vector2f delta = global_origin - global_new_origin;
    sprite.setPosition(sprite.getPosition() - delta);
    position = sprite.getPosition();
    sprite.setOrigin(new_origin);
}

void Fastener::ch_color(string color)
{
    if (color == "blue")
    {
		texture.loadFromFile("./images/fastener.png");
    }
    else if (color == "green")
    {
		texture.loadFromFile("./images/fastener_green.png");
    }
}

