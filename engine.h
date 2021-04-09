#pragma once
#include "balk.h"
#include "fastener.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <string>

using namespace std;

class Engine
{
public:
	Engine();
	void start();
private:
	void update(float time);
	void input();
	void draw();
	void add_balk();
	bool is_left_pressed;
	bool is_right_pressed;
	bool is_R_pressed;
	bool is_resize;
	bool is_gravity;
	bool is_delete;
	sf::RenderWindow window;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
	list<Balk> balks;
	vector<Fastener> fasteners;
	void draw_balk(Balk& balk);
};
