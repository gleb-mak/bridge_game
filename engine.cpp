#include "engine.h"

Engine::Engine()
{
	window.create(sf::VideoMode(1000, 800), "Game");
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
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
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
