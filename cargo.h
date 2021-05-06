#pragma once

#include <SFML/Graphics.hpp>

class Cargo 
{
public:
	Cargo();
	int GetCurrentBalk();
	void SetCurrentBalk(int current_balk_);
private:
	double mass;
	int speed;
	int current_balk;
	sf::Texture texture;
    sf::Sprite sprite;	
};
