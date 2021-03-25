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
	void update(int miliseconds);
	void input();
	void draw();
	void add_balk();
	bool is_left_pressed;
	bool is_right_pressed;
	bool is_R_pressed;
	sf::RenderWindow window;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
	list<Balk> balks;
	Fastener fastener;
//	Balk balk;
};
