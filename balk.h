#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "fastener.h"

using namespace std;

class Balk
{
public:
	Balk();
	void initialize(float position_x, float position_y, int len, double angle_, double mass_, string file);
	void update_move(sf::Vector2f pos);
	void update_rotate(float dt);
	void update_fix(sf::Vector2f fix_pos);
	void update_gravity(float time);
	sf::Sprite& get_sprite();
	bool is_move;
	bool is_rotate;
	bool is_fixed;
	bool is_select;
	vector<Fastener> fasteners; 
private:
    int len;
    double angle;
	double mass;
	double omega;
	double speed;
	sf::Vector2f position;
	sf::Texture texture;
	Balk* parent;
	sf::Sprite sprite;
	void ch_origin(sf::Vector2f new_origin);
	sf::Vector2f get_global_origin(sf::Vector2f origin);
	sf::Vector2f get_begin();
	sf::Vector2f get_end();
	void setPosition_(sf::Vector2f new_position);
	void rotate_(float angle);
};
