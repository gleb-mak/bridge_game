#include "arrow.h"

Arrow::Arrow()
{
	angle = 0;
	size = 1;
	position = sf::Vector2f(0, 0);
	is_valid = false;
	sf::Image arrow_image;
  arrow_image.loadFromFile("./images/fastener.png");

  sf::Texture arrow_texture;
  arrow_texture.loadFromImage(arrow_image);

  sf::Sprite arrow_sprite;
  arrow_sprite.setTexture(arrow_texture);

}

void Arrow::initialize(float position_x, float position_y, double angle_, int size_)
{
	position.x = position_x;
	position.y = position_y;
	angle = angle;
	size = size_;
  
	arrow_sprite.setPosition(position_x, position_y);
	arrow_sprite.setRotation(angle);
	arrow_sprite.setTextureRect(sf::IntRect(0, 0, 10, 10*size_));
	
	is_valid = true;
}

sf::Sprite& Arrow::get_sprite()
{
	return arrow_sprite;
}
