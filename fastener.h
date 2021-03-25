#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Fastener
{
public:
	Fastener();
	void initialize(float x, float y, string file);
	sf::Sprite get_sprite();
private:
	sf::Vector2f position;
	sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};
