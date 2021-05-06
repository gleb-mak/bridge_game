#include "cargo.h"

Cargo::Cargo()
{
	mass = 10.0;
	speed = 1;
	current_balk = -1;
	is_begin = false;
	is_finished = false;
	texture.loadFromFile("./images/stick.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
	sprite.setOrigin(50, 50);
    sprite.setPosition({200, 200});	
}

int Cargo::get_current_balk()
{
	return current_balk;
}

void Cargo::set_current_balk(int current_balk_)
{
	current_balk = current_balk_;
}

double Cargo::get_mass()
{
	return mass;
}

int Cargo::get_speed()
{
	return speed;
}

double Cargo::get_position()
{
	return position;
}

void Cargo::set_position(double position_)
{
	position = position_;
}

sf::Sprite Cargo::get_sprite()
{
	return sprite;
}

void Cargo::update_move(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Cargo::move_right(float dt)
{
	// sprite.setPosition(sprite.getPosition() + sf)	
}
