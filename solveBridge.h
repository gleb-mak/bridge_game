#include "chain.h"
#include <cmath>
#include "cargo.h"
#define G 10
#define MAX_FORCE 12

sf::Vector3f vector_mul (sf::Vector3f left, sf::Vector3f right);
double find_module(sf::Vector3f a);
double find_square_module(sf::Vector3f a);
double find_inertial_momentum(Chain& a);
void createSolidChains(Chain& bridge, int broken_node);
void solveBridge(Chain& bridge, Cargo& body, double dt);
