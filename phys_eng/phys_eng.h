// на вход dt время перерисовки, изначальный угол балки, гравитация
// вернуть угол на который надо повернуть балку под действием гравитации
#define EPS 0.001
#include <math.h>

double deltaAngle(int dt, double angle, double gravity)
{
	if ((fabs(angle - M_PI/2) < EPS) || (fabs(angle + M_PI/2) < EPS))
	{
		return 0;
	}	
	return 0;
}

double deltaAngle2(int dt, double angle, int l,  double gravity)
{
	if ((fabs(angle - M_PI/2) < EPS) || (fabs(angle + M_PI/2) < EPS))
	{
		return 0;
	}
	return (1.5 * (gravity/l)*cos(angle)*dt*dt);
}
