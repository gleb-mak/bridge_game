#include <iostream>

class Class
{
	int a;
};

int main()
{
	Class c;
	Class b = c;
	std::cout << &b << "\t" << &c;
	return 0;
}
