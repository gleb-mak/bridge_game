#include "engine.h"

Engine::Engine()
{
	window.create(sf::VideoMode(1000, 800), "Game");
	window.setKeyRepeatEnabled(false);
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
}

void Engine::start()
{
	sf::Clock clock;
	sf::Time dt;
	int dt_seconds = dt.asMilliseconds(); 
	while(window.isOpen())
	{
		dt = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }
		input();
		update(dt_seconds);
		draw();
	}
}

void Engine::add_balk()
{
	balks.resize(balks.size() + 1);
}
