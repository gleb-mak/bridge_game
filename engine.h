#pragma once
#include "arrow.h"
#include "balk.h"
#include "fastener.h"
#include "chain.h"
#include "cargo.h"
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
	double g;
	double resistance;
	double g_time;
	void update(double dt);
	void input();
	void draw();
	void add_balk();
	void add_arrow();
	void add_chain(Balk* b);
	bool is_left_pressed;
	bool is_right_pressed;
	bool is_R_pressed;
	bool is_resize;
	bool is_gravity;
	bool is_delete;
	sf::RenderWindow window;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
	sf::Text text;
	sf::Font font;
	list<Balk> balks;
	list<Chain> chains;
	list<Arrow> arrows;
	Cargo body;
	vector<Fastener> fasteners;
	// void draw_balk(Balk& balk);
};
