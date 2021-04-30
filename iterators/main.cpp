#include <iostream>
#include <list>

using namespace std;

int main()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	list<int>::iterator it = l.begin();
	for (auto& i : l)
	{
		cout << &i << "   ";
	}
	cout << endl;
	while (it != l.end())
	{
		cout << addressof(*(it)) << "   ";
		it++;
	}
	cout << endl;
	return 0;
}
