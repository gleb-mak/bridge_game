#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Balk
{
public:
	Balk();
	void initialize(float position_x, float position_y, int len, double angle_, double mass_, string file);
	void update(float x, float y);
	void update(double angle_);
	sf::Sprite get_sprite();
	bool is_move;
	bool is_rotate;
private:
    int len;
    double angle;
	double mass;
	sf::Vector2f position;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};
