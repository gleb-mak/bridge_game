#include "fastener.h"

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
    sprite.setOrigin(sf::Vector2f(5, 5));
    sprite.setPosition(position);
}

void Fastener::setPosition_(sf::Vector2f pos)
{
	position = pos;
	sprite.setPosition(pos);
}

sf::Sprite Fastener::get_sprite()
{
	return sprite;
}
