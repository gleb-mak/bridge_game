#include "arrow.h"

Arrow::Arrow()
{
	angle = 0;
	size = 1;
	position = sf::Vector2f(0, 0);
	is_valid = false;
	arrow_texture.loadFromFile("./images/fastener.png");
	// arrow_texture.loadFromImage(arrow_image);
	arrow_sprite.setTexture(arrow_texture);
	arrow_sprite.setTextureRect(sf::IntRect(0, 0, 10, 50*size));
	arrow_sprite.setPosition(50, 50);
}

void Arrow::initialize(float position_x, float position_y, double angle_, int size_)
{
	position.x = position_x;
	position.y = position_y;
	angle = angle;
	size = size_;

	arrow_texture.loadFromFile("./images/fastener.png");
    arrow_sprite.setTexture(arrow_texture);
    arrow_sprite.setTextureRect(sf::IntRect(0, 0, 10, 50));
    // setPosition_(position);
    // rotate_(angle);
	arrow_sprite.setPosition(position_x, position_y);
	arrow_sprite.setRotation(angle);
	
	// arrow_sprite.setTextureRect(sf::IntRect(0, 0, 10, 50*size_));
	is_valid = true;
}

sf::Sprite& Arrow::get_sprite()
{
	return arrow_sprite;
}
