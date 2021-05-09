#include "cargo.h"

Cargo::Cargo()
{
	mass = 10.0;
	speed = 0.2;
	current_balk = -1;
	is_initialized = false;
	is_begin = false;
	is_finished = false;
	texture.loadFromFile("./images/cat.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 1406, 827));
	sprite.setOrigin(703, 827);
	sprite.setScale(0.05f, 0.05f);
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

float Cargo::get_speed()
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
