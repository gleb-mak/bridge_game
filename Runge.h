static const double one_sixth = 1.0 / 6.0;
void Runge_Kutta_2nd_Order( double (*f)(double, double, double), double x0,
                        double y[], double c, double h, int number_of_steps );

