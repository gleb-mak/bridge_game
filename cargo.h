#pragma once

#include <SFML/Graphics.hpp>

class Cargo 
{
public:
	Cargo();
	int get_current_balk();
	void set_current_balk(int current_balk_);
	double get_mass();
	int get_speed();
	double get_position();
	void set_position(double position_);
	bool is_finished;
private:
	double position;
	double mass;
	int speed;
	int current_balk;
	sf::Texture texture;
    sf::Sprite sprite;	
};
