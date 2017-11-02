#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "DeckOfCards.h"
#include "Hand.h"
#include "Dice.h"
#include "Dice_rolling.h"
#include "Continent.h"

class Country;
using namespace std;

class Player
{

private:
	Hand hand;
	Dice_rolling d1;
	vector <Country*> countries;
	int numOfChosenDices;

public:
	Player();
	~Player();
	void pickCard(DeckOfCards &d);
	void addCountry(Country *c);
	void removeCountry(int);
	void Reinforce();
	int* Attack(int);
	void Fortify();
	int GetNumOfCountry();
	Country * GetCountryInPosition(int position);
	void AddArmytoCountry(Country * c);
	int GetTotalArmySize();
	int * Defend(int);
	int* sort(int*);
	void printCountries();
	int searchCountry(string name);
	bool OwnsContinent();
	void printHand();
	int getNumDices();
	Hand* getHand();
	vector<Continent*> continents;

};
