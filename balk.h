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
	void setPosition_(sf::Vector2f new_position);
	void initialize(float position_x, float position_y, int len, double angle_, double mass_, string file);
	void update(float x, float y);
	void update(float dt);
	void update(sf::Vector2f dist);
	void update_gravity(float time);
	sf::Sprite get_sprite();
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
	sf::Sprite sprite;
	void ch_origin(sf::Vector2f new_origin);
	sf::Vector2f get_global_origin(sf::Vector2f origin);
	sf::Vector2f get_begin();
	sf::Vector2f get_end();
	Balk* next;
	Balk* prev;
};
