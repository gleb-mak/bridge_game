#include "cargo.h"

Cargo::Cargo()
{
	mass = 10.0;
	speed = 1;
	current_balk = -1;
	texture.loadFromFile("./images/stick.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    sprite.setPosition({200, 200});	
}

int Cargo::GetCurrentBalk()
{
	return current_balk;
}

void Cargo::SetCurrentBalk(int current_balk_)
{
	current_balk = current_balk_;
}
