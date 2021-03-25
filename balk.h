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
	void update(int dt);
	void update(sf::Vector2f dist);
	sf::Sprite get_sprite();
	bool is_move;
	bool is_rotate;
	bool is_fixed;
	bool is_select;
private:
    int len;
    double angle;
	double mass;
	double omega;
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;
};
