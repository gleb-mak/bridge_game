#include "chain.h"
#include "Runge.h"
#include <cmath>
#define G 0.0005

Chain::Chain()
{
	number_of_balks = 0;
	is_broken = false;
	is_fixed = false;
}

Chain::Chain(Balk* b)
{
	balks.push_back(b);
	number_of_balks = 1;
	is_broken = false;
	is_fixed = false;
}

void Chain::initialize(int n, vector<Balk*>& b)
{
	number_of_balks = n;
	balks = b;
	is_broken = false;
    is_fixed = false;
}

void Chain::add_balk(Balk* b)
{
	balks.push_back(b);
	number_of_balks++;
}

double Chain::get_mass()
{
	double mass = 0;
	for (auto& balk : balks)
	{
		mass += balk->get_mass();
	}
	return mass;
}

void Chain::update_gravity(double dt, double t)
{
	rotate_all(0.1);
	return;
	if (size() == 2)
	{
		double m1 = balks[0]->get_mass();
		double m2 = balks[1]->get_mass();
		double l1 = balks[0]->get_len();
		double l2 = balks[1]->get_len();
		double o1 = balks[0]->get_omega();
		double o2 = balks[1]->get_omega();
		double y1 = balks[0]->get_sprite().getRotation() * M_PI/180;
		double y2 = balks[1]->get_sprite().getRotation() * M_PI/180;
		double p1 = balks[0]->get_omega();
		double p2 = balks[1]->get_omega();
		std::vector<double> new_val(4);
		new_val = Runge_Kutta_4_eq(t, dt, p1, p2, y1, y2, l1, l2, m1, m2, G);
		balks[0]->set_omega(new_val[2]);
		balks[1]->set_omega(new_val[3]);
		balks[0]->rotate_(-(y1 - new_val[0])*180/M_PI);
		balks[1]->rotate_(-(y2 - new_val[1])*180/M_PI);
	}
}

vector<Balk*>& Chain::get_balks()
{
	return balks;
}

int Chain::size()
{
	return balks.size();
}

void Chain::delete_end()
{
	balks.erase(balks.begin() + size());
	number_of_balks--;
}

Chain Chain::copy()
{
	Chain chain_copy;
	chain_copy.initialize(number_of_balks, balks);
	return chain_copy;
}

Chain Chain::copy_to_element(Balk* el)
{
	Chain chain_copy = copy();
	for (int i = size(); i != 0; i--)
	{
		if (chain_copy.get_balks()[i] != el)
		{
			chain_copy.delete_end();
		}
		else
		{
			break;
		}
	}
	return chain_copy;
}

void Chain::SetLen(int len)
{
	balks.resize(len);
}

int Chain::GetLen()
{
	return balks.size();
}

void Chain::Clear()
{
	balks.clear();
}

void Chain::SetMoment(double moment)
{
	inertial_momentum = moment;
}

double Chain::GetMoment()
{
	return inertial_momentum;
}

Balk& Chain::operator[](int index)
{
	return *balks[index];
}

void Chain::ch_is_broken()
{
	is_broken = !is_broken;
}

bool Chain::get_is_broken()
{
	return is_broken;
}

void Chain::rotate_all(float angle)
{
	for (auto& balk : balks)
	{
		balk->rotate_(angle);
	}
}
