#include "arrow.h"

Arrow::Arrow()
{
	angle = 0;
	size = 1;
	position = sf::Vector2f(0, 0);
	is_valid = false;
	arrow_texture.loadFromFile("./images/arrow.png");
	// arrow_texture.loadFromImage(arrow_image);
	arrow_sprite.setTexture(arrow_texture);
	arrow_sprite.setTextureRect(sf::IntRect(0, 0, 25, 74));
	arrow_sprite.setOrigin(12, 0);
	// arrow_sprite.setScale(0.015f, 0.03f);
	arrow_sprite.setPosition(50, 50);
}

void Arrow::initialize(float position_x, float position_y, double angle_, int size_)
{
	position.x = position_x;
	position.y = position_y;
	angle = angle_;
	size = size_;

	arrow_texture.loadFromFile("./images/arrow.png");
    arrow_sprite.setTexture(arrow_texture);
    arrow_sprite.setTextureRect(sf::IntRect(0, 0, 25, 74));
	arrow_sprite.setOrigin(12, 0);
	arrow_sprite.setScale(1, ((float)size/74.0));
    // setPosition_(position);
    // rotate_(angle);
	arrow_sprite.setPosition(position_x, position_y);
	arrow_sprite.setRotation(angle_);
	
	is_valid = true;
}

sf::Sprite& Arrow::get_sprite()
{
	return arrow_sprite;
}
