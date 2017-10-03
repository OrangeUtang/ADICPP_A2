#include "Dice_rolling.h"
#include <iostream>

using namespace std;
int NumOfDices = 0;
int countRoll = 0;

void Dice_rolling::roll()
{

	while (NumOfDices < 1 || NumOfDices >3) {
		cout << endl << "Select the number of dice you want to roll (1 to 3): ";
		cin >> NumOfDices;
	}

	switch (NumOfDices)
	{
	case 1:
		dice1.generate_value();
		container[0] = dice1.get_dice();
		nb_values(container[0]);
		cout << "Values of roll : " << container[0];
		countRoll++;
		break;
	case 2:
		dice1.generate_value();
		container[0] = dice1.get_dice();
		nb_values(container[0]);
		dice2.generate_value();
		container[1] = dice2.get_dice();
		nb_values(container[1]);
		cout << "Values of roll : " << container[0] << " and " << container[1];
		countRoll += 2;
		break;

	case 3:
		dice1.generate_value();
		container[0] = dice1.get_dice();
		nb_values(container[0]);
		dice2.generate_value();
		container[1] = dice2.get_dice();
		nb_values(container[1]);
		dice3.generate_value();
		container[2] = dice3.get_dice();
		nb_values(container[2]);
		cout << "Values of roll : " << container[0] << ", " << container[1] << " and " << container[2];
		countRoll += 3;
		break;

	default: cout << "Wrong number of dice ";
		break;
	}

	set_percentage();
	//reinitialize number of dices
	NumOfDices = 0;

}

void Dice_rolling::set_percentage()
{

	perc_of_values[0] = 100.0 * (nb_of_values[0]) / static_cast<double>(countRoll);
	perc_of_values[1] = 100.0 * (nb_of_values[1]) / static_cast<double>(countRoll);
	perc_of_values[2] = 100.0 * (nb_of_values[2]) / static_cast<double>(countRoll);
	perc_of_values[3] = 100.0 * (nb_of_values[3]) / static_cast<double>(countRoll);
	perc_of_values[4] = 100.0 * (nb_of_values[4]) / static_cast<double>(countRoll);
	perc_of_values[5] = 100.0 * (nb_of_values[5]) / static_cast<double>(countRoll);


}


void Dice_rolling::get_values()
{
	switch (NumOfDices) {
	case 1:
		cout << container[0]; break;
	case 2:
		cout << container[0] << ", " << container[1]; break;
	case 3:
		cout << container[0] << ", " << container[1] << ", " << container[2]; break;
	}

}

void Dice_rolling::getCountRoll()
{
	cout << endl << "countRoll is : " << double(countRoll);
}

void Dice_rolling::nb_values(int x)
{
	switch (x) {

	case 1: nb_of_values[0]++; break;
	case 2: nb_of_values[1]++; break;
	case 3: nb_of_values[2]++; break;
	case 4: nb_of_values[3]++; break;
	case 5: nb_of_values[4]++; break;
	case 6: nb_of_values[5]++; break;


	}

}

void Dice_rolling::printperc()
{
	for (int x = 0; x < 6; x++)
	{
		double val = perc_of_values[x];
		cout << endl << "percentage of " << x + 1 << ": " << val << "%";
	}
}

void Dice_rolling::printNb()
{
	cout << endl << "nb_values array : ";

	for (int x = 0; x < 6; x++)
	{
		double val = nb_of_values[x];
		cout << endl << "percentage of " << x + 1 << ": " << val;
	}

}








