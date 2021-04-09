#include "Runge.h"
#include <cmath>

void Runge_Kutta_2nd_Order( double (*f)(double, double, double, double, double), double x0,
                        double y[], double& c, double h, int number_of_steps, double len, double mass ) {

   double k1, k2, k3, k4;
   double h2 = 0.5 * h;
   double ych2;
   int i;

   for (i = 0; i < number_of_steps; x0 += h, i++) {
      ych2 = y[i] + c * h2;
      k1 = h * (*f)(x0, y[i], c, len, mass);
      k2 = h * (*f)(x0+h2, ych2, c + 0.5 * k1, len, mass);
      k3 = h * (*f)(x0+h2, ych2 + 0.25 * k1 * h, c + 0.5 * k2, len, mass);
      k4 = h * (*f)(x0+h, y[i] + c * h + h2 * k2 , c + k3, len, mass);
      y[i+1] = y[i] + ( c + one_sixth * (k1 + k2 + k3) ) * h;
      c += one_sixth * ( k1 + k2 + k2 + k3 + k3 + k4 );
   }
         //printf("the initial alpha is %lf, the next alpha is %lf, the curr speed is %lf\n", y[0], y[1], c  );

}

double vectors_multiply(sf::Vector2f v1, sf::Vector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

double vector_abs(sf::Vector2f v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

double angle_2_vectors(sf::Vector2f v1, sf::Vector2f v2)
{
    return acos(vectors_multiply(v1, v2) / (vector_abs(v1) * vector_abs(v2)));
}

sf::Vector2f global_to_local(sf::Vector2f v_global, float alpha)
{
    alpha = alpha * M_PI / 180;
    sf::Vector2f i_1;
    sf::Vector2f i_2;
    i_1.x = cos(alpha);
    i_1.y = - sin(alpha);
    i_2.x = sin(alpha);
    i_2.y = cos(alpha);
    return v_global.x * i_1 + v_global.y * i_2;
}

sf::Vector2f get_global_origin(sf::Vector2f origin, sf::Sprite& sprite)
{
    float alpha = sprite.getRotation() * M_PI / 180;
    sf::Vector2f j_1;
    j_1.x = -sin(alpha - M_PI / 2);
    j_1.y = cos(alpha - M_PI / 2);
    sf::Vector2f j_2;
    j_2.x = -sin(alpha);
    j_2.y = cos(alpha);
    return origin.x * j_1 + origin.y * j_2;
}

