#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

sf::Vector2f get_global_origin(sf::Sprite& sprite, sf::Vector2f origin)
{
	float alpha = sprite.getRotation() * M_PI / 180;
    sf::Vector2f j_1;
    j_1.x = -sin(alpha - M_PI / 2);
    j_1.y = cos(alpha - M_PI / 2);
    sf::Vector2f j_2;
    j_2.x = -sin(alpha);
    j_2.y = cos(alpha);
	return origin.x * j_1 + origin.y * j_2;
}

void ch_origin(sf::Vector2f new_origin, sf::Sprite& sprite)
{
	sf::Vector2f global_origin = get_global_origin(sprite, sprite.getOrigin());
	sf::Vector2f global_new_origin = get_global_origin(sprite, new_origin);
	sf::Vector2f delta = global_origin - global_new_origin;
	sprite.setPosition(sprite.getPosition() - delta);
	sprite.setOrigin(new_origin);
}

int main()
{
	sf::RenderWindow window;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	window.create(sf::VideoMode(1000, 800), "Game");	
	texture.loadFromFile("../images/stick.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 100));
    sprite.setRotation(51);
	sprite.setOrigin(3, 20);
    position = {500, 400};
    sprite.setPosition(position);
	while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			ch_origin(sf::Vector2f(50, 50), sprite);
			sprite.rotate(10);
			cout << sprite.getOrigin().x << " " << sprite.getOrigin().y;
		}
		window.draw(sprite);
		window.display();
    }
	return 0;
}
