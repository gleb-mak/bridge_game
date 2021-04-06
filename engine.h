#pragma once
#include "balk.h"
#include "fastener.h"
#include <SFML/Graphics.hpp>
#include <list>
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
	bool is_L_pressed;
	bool is_gravity;
	sf::RenderWindow window;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
	list<Balk> balks;
	Fastener fastener;
	void draw_balk(Balk& balk);
//	Balk balk;
};
