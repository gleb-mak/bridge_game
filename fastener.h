#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Fastener
{
public:
	Fastener();
	void initialize(sf::Vector2f pos, string file);
	sf::Sprite& get_sprite();
	sf::Texture& get_texture();
	void setPosition_(sf::Vector2f pos);
	sf::Vector2f get_global_origin(sf::Vector2f origin);
	void ch_origin(sf::Vector2f new_origin);
private:
	sf::Vector2f position;
	sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};
