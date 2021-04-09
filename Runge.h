#pragma once
#include <SFML/Graphics.hpp>

static const double one_sixth = 1.0 / 6.0;

void Runge_Kutta_2nd_Order( double (*f)(double, double, double, double, double), double x0, double y[], double& c, double h, int number_of_steps, double len, double mass );

double vectors_multiply(sf::Vector2f v1, sf::Vector2f v2);

double vector_abs(sf::Vector2f v);

double angle_2_vectors(sf::Vector2f v1, sf::Vector2f v2);

sf::Vector2f global_to_local(sf::Vector2f v_global, float alpha);

sf::Vector2f get_global_origin(sf::Vector2f origin, sf::Sprite& sprite);

