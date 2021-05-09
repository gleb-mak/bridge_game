#include "Runge.h"
#include "chain.h"
#include <cmath>
#include <functional>
#include <iostream>
#define REZIST_MOMENTUM 0.001

using namespace std::placeholders;
sf::Vector3f vector_mul(sf::Vector3f left, sf::Vector3f right)
{
    return (sf::Vector3f(left.y*right.z - left.z*right.y, -(left.x*right.z - left.z*right.x), left.x*right.y - left.y*right.x));
}

sf::Vector3f normalize_vector(sf::Vector3f v)
{
  return v/(float)find_module(v);
}

double scalar_product (sf::Vector3f a, sf::Vector3f b)
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

double find_module(sf::Vector3f a)
{
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

double find_square_module(sf::Vector3f a)
{
    return (a.x*a.x + a.y*a.y + a.z*a.z);
}

double f(double x, double y, double z, double m, double g, double l)
{
    return ((3 * g * sin(y))/(2 * l)) - (z/( (z == 0) ? 1 : fabs(z) )) * (3 * REZIST_MOMENTUM) / (m * l * l);
}

double f_chain(double x, double y, double z, double m, double g, double l, double I)
{
    return (m * g * l * sin(y) - (z/( (z == 0) ? 1 : fabs(z) )) * REZIST_MOMENTUM) / I;
}

double g(double x, double y, double z)
{
		return (z);
}

double A1(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return (p1 * p2 * sin(y1 - y2)) / (l1 * l2 * (m1 + m2 * pow(sin(y1 - y2), 2)));
}

double A2(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return ((p1 * p1 * m2 * l2 * l2 - 2 * p1 * p2 * m2 * l1 * l2 * cos(y1 - y2) + p2 * p2 * (m1 + m2) * l1 * l1) * sin(2 * (y1 - y2))) / (2 * l1 * l1 * l2 * l2 * pow((m1 + m2 * pow(sin(y1 - y2), 2)), 2));
}

double F1(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return (p1 * l2 - p2 * l1 * cos(y1 - y2)) / (l1 * l1 * l2 * (m1 + m2 * pow(sin(y1 - y2), 2)));
}

double F2(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return (p2 * (m1 + m2) * l1 - p1 * m2 * l2 * cos(y1 - y2)) / (m2 * l1 * l2 * l2 * (m1 + m2 * pow(sin(y1 - y2), 2)));
}	

double F3(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return -(m1 + m2) * g * l1 * sin(y1) - A1(p1, p2, y1, y2, l1, l2, m1, m2, g) + A2(p1, p2, y1, y2, l1, l2, m1, m2, g);
}

double F4(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return -m2 * g * l2 * sin(y2) + A1(p1, p2, y1, y2, l1, l2, m1, m2, g) - A2(p1, p2, y1, y2, l1, l2, m1, m2, g);
}

double f1(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return p1;
}

double f2(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return p2;
}

double f3(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return (-g*(2*m1+m2)*sin(y1) - m2*g*sin(y1-2*y2) - 2*sin(y1-y2)*m2*(p2*p2*l2+p1*p1*l1*cos(y1-y2))) / (l1*(2*m2+m2-m2*cos(2*y1-2*y2)));
}

double f4(double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	return (2*sin(y1-y2)*(p1*p1*l1*(m1+m2)+g*(m1+m2)*cos(y1)+p2*p2*l2*m2*cos(y1-y2))) / (l2*(2*m1+m2-m2*cos(2*y1-2*y2)));
}
//I * a'' = r_c *MG + M_tr
// double integrate_chain(double x, double y, double z, double m, double g, double l) //x - t, y - angle, z - omega
// {
// 	return 
	// return -((vector_mul(chain.mass_center, (float)chain.get_mass()*sf::Vector3f(0, -(float)g, 0)).z + REZIST_MOMENTUM)/chain.GetMoment());
// }

double Runge_Kutta(double Yo, double Xo, double& Zo, double dt, double m, double G, double l, double I) //y - angle, x - t, z - ome
{
	double Y1, Z1;
	double k1, k2, k4, k3;
	double q1, q2, q4, q3;
	int n = 5;
	double h = dt / n;
	auto f1 = std::bind(f_chain, _1, _2, _3, m, G, l, I);
	for (int i = 0; i < n; ++i)
	{
		k1 = h * f1(Xo, Yo, Zo);
		q1 = h * g(Xo, Yo, Zo);
		
		k2 = h * f1(Xo + h/2.0, Yo + q1/2.0, Zo + k1/2.0);
		q2 = h * g(Xo + h/2.0, Yo + q1/2.0, Zo + k1/2.0);
		
		k3 = h * f1(Xo + h/2.0, Yo + q2/2.0, Zo + k2/2.0);
		q3 = h * g(Xo + h/2.0, Yo + q2/2.0, Zo + k2/2.0);
		
		k4 = h * f1(Xo + h, Yo + q3, Zo + k3);
		q4 = h * g(Xo + h, Yo + q3, Zo + k3);
		
		Z1 = Zo + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;
		Y1 = Yo + (q1 + 2.0*q2 + 2.0*q3 + q4)/6.0;

		Yo = Y1;
		Zo = Z1;
		Xo += h;
	}
	return Y1;
}

void Runge_Kutta_2nd_Order( double (*f)(double, double, double, double, double), double x0,
                        double y[], double& c, double dt, int number_of_steps, double len, double mass ) {

   double k1, k2, k3, k4;
   double h = dt / number_of_steps;
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

std::vector<double> Runge_Kutta_4_eq(double t0, double dt, double p1, double p2, double y1, double y2, double l1, double l2, double m1, double m2, double g)
{
	std::vector<double> ans(4);
	double y1_new, y2_new, p1_new, p2_new;
	std::vector<double> k1(4), k2(4), k3(4), k4(4);
	int n = 5;
	double h = dt / n;
	auto g1 = std::bind(f1, _1, _2, _3, _4, l1, l2, m1, m2, g);
    auto g2 = std::bind(f2, _1, _2, _3, _4, l1, l2, m1, m2, g);
    auto g3 = std::bind(f3, _1, _2, _3, _4, l1, l2, m1, m2, g);
    auto g4 = std::bind(f4, _1, _2, _3, _4, l1, l2, m1, m2, g);

	for (int i = 0; i < n; ++i)
	{
		k1[0] = h * g1(p1, p2, y1, y2);
		k1[1] = h * g2(p1, p2, y1, y2);
		k1[2] = h * g3(p1, p2, y1, y2);
		k1[3] = h * g4(p1, p2, y1, y2);

		k2[0] = h * g1(p1 + k1[2]/2.0, p2 + k1[3]/2.0, y1 + k1[0]/2.0, y2 + k1[1]/2.0);
		k2[1] = h * g2(p1 + k1[2]/2.0, p2 + k1[3]/2.0, y1 + k1[0]/2.0, y2 + k1[1]/2.0);
		k2[2] = h * g3(p1 + k1[2]/2.0, p2 + k1[3]/2.0, y1 + k1[0]/2.0, y2 + k1[1]/2.0);
		k2[3] = h * g4(p1 + k1[2]/2.0, p2 + k1[3]/2.0, y1 + k1[0]/2.0, y2 + k1[1]/2.0);
		
		k3[0] = h * g1(p1 + k2[2]/2.0, p2 + k2[3]/2.0, y1 + k2[0]/2.0, y2 + k2[1]/2.0);
		k3[1] = h * g2(p1 + k2[2]/2.0, p2 + k2[3]/2.0, y1 + k2[0]/2.0, y2 + k2[1]/2.0);
		k3[2] = h * g3(p1 + k2[2]/2.0, p2 + k2[3]/2.0, y1 + k2[0]/2.0, y2 + k2[1]/2.0);
		k3[3] = h * g4(p1 + k2[2]/2.0, p2 + k2[3]/2.0, y1 + k2[0]/2.0, y2 + k2[1]/2.0);
		
		k4[0] = h * g1(p1 + k3[2]/2.0, p2 + k3[3]/2.0, y1 + k3[0]/2.0, y2 + k3[1]/2.0);
		k4[1] = h * g2(p1 + k3[2]/2.0, p2 + k3[3]/2.0, y1 + k3[0]/2.0, y2 + k3[1]/2.0);
		k4[2] = h * g3(p1 + k3[2]/2.0, p2 + k3[3]/2.0, y1 + k3[0]/2.0, y2 + k3[1]/2.0);
		k4[3] = h * g4(p1 + k3[2]/2.0, p2 + k3[3]/2.0, y1 + k3[0]/2.0, y2 + k3[1]/2.0);
		
		y1_new = y1 + (k1[0] + 2.0*k2[0] + 2.0*k3[0] + k4[0])/6.0;
        y2_new = y2 + (k1[1] + 2.0*k2[1] + 2.0*k3[1] + k4[1])/6.0;
        p1_new = p1 + (k1[2] + 2.0*k2[2] + 2.0*k3[2] + k4[2])/6.0;
        p2_new = p2 + (k1[3] + 2.0*k2[3] + 2.0*k3[3] + k4[3])/6.0;

		y1 = y1_new;
		y2 = y2_new;
		p1 = p1_new;
		p2 = p2_new;
		t0 += h;
	}
	ans[0] = y1;
	ans[1] = y2;
	// ans[2] = g1(p1, p2, y1, y2);
	// ans[3] = g2(p1, p2, y1, y2);
	ans[2] = p1;
	ans[3] = p2;
	// std::cout << y1 << "\t" << y2 << "\n";
	return ans;
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
