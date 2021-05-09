#pragma once
#include <vector>
#include "balk.h"
#include "arrow.h"
#include <list>

class Chain
{
public:
	Chain();
	Chain(Balk* b);
	void initialize(int n, vector<Balk*>& b);
	void add_balk(Balk* b);
	void update_gravity(double dt, double t);
	void rotate_all(float angle);
	vector<Balk*>& get_balks();
	int size();
	Chain copy();
	Chain copy_to_element(Balk* element);
	void delete_end();
	void SetLen(int len);
	int GetLen();
	void Clear();
	void SetMoment(double moment);
	double GetMoment();
	void ch_is_broken();
	bool get_is_broken();
	Balk& operator[](int index);
	bool is_fixed;
	sf::Vector3f mass_center;
	double get_mass();
private:
	bool is_broken;
	double inertial_momentum;
	int number_of_balks;
	vector<Balk*> balks;
};
