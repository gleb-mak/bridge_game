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
	void update_move(sf::Vector2f pos);
	void move_right(float dt);
	bool is_begin;
	bool is_finished;
	bool is_initialized;
	sf::Sprite get_sprite();
private:
	double position;
	double mass;
	int speed;
	int current_balk;
	sf::Texture texture;
    sf::Sprite sprite;	
};
