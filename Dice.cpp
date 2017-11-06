#include "Dice.h"
#include <random>
#include <functional>

using namespace std;

void Dice::set_dice(int x)
{
	value = x;
}

int Dice::get_dice()
{
	return value;
}

void Dice::generate_value()
{
	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> dice(1, 6); // distribute results between 1 and 6 inclusive.  

		int v = dice(gen);
		set_dice(v);
	
}
