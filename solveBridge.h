#include <cmath>
#include <list>
#include "cargo.h"
#include "chain.h"
#include "arrow.h"
#define MAX_FORCE 120

sf::Vector3f vector_mul (sf::Vector3f left, sf::Vector3f right);
void createSolidChains(Chain& bridge, int broken_node);
void solveBridge(Chain& bridge, Cargo& body, double dt, std::list<Arrow>& arrows, double t);
