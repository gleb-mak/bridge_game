#include "engine.h"

Engine::Engine()
{
	window.create(sf::VideoMode(1000, 800), "Game");
//	window.setKeyRepeatEnabled(false);
	balks.resize(3);
	int i = 1;
	for (auto& balk : balks)
	{
		balk.initialize((float)100 * i, (float)100, 100, 100, 1, "stick.png");
		i++;
	}
	is_left_pressed = false;
	is_right_pressed = false;
	is_R_pressed = false;
	is_gravity = false;
}

void Engine::start()
{
	sf::Clock clock;
	while(window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time/800;
		// sf::Event event;
		// while (window.pollEvent(event))
        // {
        //     if (event.type == sf::Event::Closed)
        //     window.close();
        // }
		input();
		update(time);
		draw();
	}
}

void Engine::add_balk()
{
	balks.resize(balks.size() + 1);
}
