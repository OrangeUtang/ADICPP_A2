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
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 6);
	int v = distribution(generator);
	set_dice(v); 
	//random_device rd;   // non-deterministic generator  
	//mt19937 gen(rd());  // to seed mersenne twister.  
	//uniform_int_distribution<> dice(1, 6); // distribute results equally between 1 and 6 inclusive.  
    //= dice(gen);
	

}
