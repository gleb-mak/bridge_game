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

void Fastener::initialize(float x, float y, string file)
{
	position.x = x;
	position.y = y;
	texture.loadFromFile("./images/" + file);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setOrigin(sf::Vector2f(5, 5));
    sprite.setPosition(position);
}

sf::Sprite Fastener::get_sprite()
{
	return sprite;
}
