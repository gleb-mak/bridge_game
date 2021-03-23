#include "balk.h"

Balk::Balk()
{
	begin = {100, 100};
    len = 100;
    angle = 20;
	mass = 1;
    texture.loadFromFile("./images/stick.png");
//  texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 100));
	sprite.setRotation(angle);
    sprite.setPosition(100, 100);
}

Balk::Balk(sf::Vector2f begin_, int len_, double angle_, double mass_, string file)
{
	begin = {100, 100};
	len = 100;
	angle = 20;
	mass = mass_;
	texture.loadFromFile("./images/stick.png");
//	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 10, 100));
	sprite.setPosition(100, 100);
}

void Balk::update(float sec)
{
	sprite.setPosition(100, 200);
}

sf::Sprite Balk::get_sprite()
{
	return sprite;
}
