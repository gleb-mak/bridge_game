#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Fastener
{
public:
	Fastener();
	void initialize(sf::Vector2f pos, string file);
	sf::Sprite get_sprite();
	void setPosition_(sf::Vector2f pos);
private:
	sf::Vector2f position;
	sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};
