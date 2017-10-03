#pragma once
#include "Dice.h"
#include <string>

class Dice_rolling
{
private:

	Dice dice1;
	Dice dice2;
	Dice dice3;
	int container[3];
	int nb_of_values[6] = { 0,0,0,0,0,0 };
	double perc_of_values[6] = { 0,0,0,0,0,0 };

public:

	void roll();

	void set_percentage();

	void get_values();

	void getCountRoll();

	void nb_values(int x);

	void printperc();

	void printNb();



};

