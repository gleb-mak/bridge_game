#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Arrow
{
public:
	Arrow();
	void initialize(float position_x, float position_y, double angle_, int size_);
	sf::Sprite& get_sprite();
	double angle;
	sf::Vector2f position;
	bool is_valid;
	int size;
private:
	sf::Texture arrow_texture;
	sf::Sprite arrow_sprite;
	sf::Image arrow_image;
};
