#include "engine.h"

Engine::Engine()
{
	g_time = 0.0;
	window.create(sf::VideoMode(1000, 800), "Game");
	g = 9.81; 
	font.loadFromFile("./images/font.ttf");
	string str = "G: " + to_string(g);
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(50 ,750);
	balks.resize(2);
	fasteners.resize(2);
	int i = 1;
	for (auto& balk : balks)
	{
		balk.initialize(100.f * i, 100.f, 100, 0, 1, "stick.png");
		i++;
	}
	fasteners[0].initialize(sf::Vector2f(200, 400), "fastener.png");
	fasteners[1].initialize(sf::Vector2f(800, 400), "fastener.png");
	is_left_pressed = false;
	is_right_pressed = false;
	is_R_pressed = false;
	is_resize = false;
	is_gravity = false;
	is_delete = false;
}

void Engine::start()
{
	sf::Clock clock;
	while(window.isOpen())
	{
		double time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 800;
		input();
		update(time);
		draw();
	}
}

void Engine::add_balk()
{
	balks.resize(balks.size() + 1);
}

void Engine::add_chain(Balk* b)
{
	chains.push_back(b);
}
