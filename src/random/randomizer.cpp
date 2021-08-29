#include "../../includes/random/randomizer.h"

g2d::random::randomizer::randomizer()
{
	this->_randomer.seed((unsigned long long int)time(NULL));
	srand((unsigned long long int) time(NULL));
}

g2d::random::randomizer::~randomizer()
{
}

void g2d::random::randomizer::seed()
{
	this->_randomer.seed((unsigned long long int)time(NULL));
}

