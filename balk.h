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
	~Balk();
	void initialize(float position_x, float position_y, double len, double angle_, double mass_, string file);
	void update_move(sf::Vector2f pos);
	void update_rotate(float dt);
	void update_fix(sf::Vector2f fix_pos);
	void update_end_fix(sf::Vector2f fix_pos);
	void update_gravity(double dt, double t);
	void update_become_child(Balk* p);
	void update_child();
	void update_len_inc();
	void update_size(sf::Vector2f mouse_pos);
	sf::Sprite& get_sprite();
	void set_parent(Balk* b);
	sf::Vector2f get_end();
	sf::Vector2f len_vector();
	bool is_move;
	bool is_rotate;
	bool is_fixed;
	bool is_end_fixed;
	bool is_select;
	bool is_child;
	bool is_parent;
	bool is_resize;
	bool is_in_fixed_chain;
	int child_number;
	vector<Fastener> fasteners;
	double get_mass();
	double get_len();
	double get_omega();
	void rotate_(float angle);
	void set_omega(double new_omega);
private:
    double len;
    double angle;
	double mass;
	double ro;
	double omega;
	double speed;
	sf::Vector2f position;
	sf::Texture texture;
	Balk* parent;
	sf::Sprite sprite;
	void ch_origin(sf::Vector2f new_origin);
	sf::Vector2f get_begin();
	void setPosition_(sf::Vector2f new_position);
	void setRotation_(float angle);
	static double movement_ODE(double t, double angle, double c, double len, double mass);
	void set_len(double new_len);
};
