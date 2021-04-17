#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

static const double one_sixth = 1.0 / 6.0;

double Runge_Kutta(double Yo, double Xo, double& Zo, double h, double m, double G, double l);

void Runge_Kutta_2nd_Order( double (*f)(double, double, double, double, double), double x0, double y[], double& c, double h, int number_of_steps, double len, double mass );

std::vector<double> Runge_Kutta_4_eq(double t0, double dt, double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g);


double vectors_multiply(sf::Vector2f v1, sf::Vector2f v2);

double vector_abs(sf::Vector2f v);

double angle_2_vectors(sf::Vector2f v1, sf::Vector2f v2);

sf::Vector2f global_to_local(sf::Vector2f v_global, float alpha);

sf::Vector2f get_global_origin(sf::Vector2f origin, sf::Sprite& sprite);

