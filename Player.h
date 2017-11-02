#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "DeckOfCards.h"
#include "Hand.h"
#include "Dice.h"
#include "Dice_rolling.h"
class Country;

class Player
{

private:
	Hand *hand;
	Dice_rolling d1;
	vector <Country*> countries;
	int numOfChosenDices;

public:
	Player();
	~Player();
	void pickCard(DeckOfCards &d);
	void addCountry(Country *c);
	void removeCountry(int);
	void reinforce();
	//int* attack(int);
	bool fortify(Country*, Country*, int);
	int GetNumOfCountry();
	Country * GetCountryInPosition(int position);
	void AddArmytoCountry(Country * c);
	int GetTotalArmySize();
	//int * defend(int);
	int* sort(int*);
	void printCountries();
	int searchCountry(string name);
	void printHand();
	int getNumDices();
};
