#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Balk
{
public:
	Balk();
    Balk(sf::Vector2f begin_, int len, double angle_, double mass_, string file);
	void update(float sec);
	sf::Sprite get_sprite();
private:
	sf::Vector2f begin;
    int len;
    double angle;
	double mass;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};
