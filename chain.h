#pragma once
#include <vector>
#include "balk.h"

class Chain
{
public:
	Chain();
	Chain(Balk* b);
	void initialize(int n, vector<Balk*>& b);
	void add_balk(Balk* b);
	void update_gravity(double dt, double t);
	vector<Balk*>& get_balks();
	int size();
	Chain copy();
	Chain copy_to_element(Balk* element);
	void delete_end();
private:
	int number_of_balks;
	vector<Balk*> balks;
};
