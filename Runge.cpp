#include "Runge.h"

void Runge_Kutta_2nd_Order( double (*f)(double, double, double, double, double), double x0,
                        double y[], double& c, double h, int number_of_steps ) {

   double k1, k2, k3, k4;
   double h2 = 0.5 * h;
   double ych2;
   int i;

   for (i = 0; i < number_of_steps; x0 += h, i++) {
      ych2 = y[i] + c * h2;
      k1 = h * (*f)(x0, y[i], c, 100, 1);
      k2 = h * (*f)(x0+h2, ych2, c + 0.5 * k1, 100, 1);
      k3 = h * (*f)(x0+h2, ych2 + 0.25 * k1 * h, c + 0.5 * k2, 100, 1);
      k4 = h * (*f)(x0+h, y[i] + c * h + h2 * k2 , c + k3, 100, 1);
      y[i+1] = y[i] + ( c + one_sixth * (k1 + k2 + k3) ) * h;
      c += one_sixth * ( k1 + k2 + k2 + k3 + k3 + k4 );
   }
         //printf("the initial alpha is %lf, the next alpha is %lf, the curr speed is %lf\n", y[0], y[1], c  );

}
