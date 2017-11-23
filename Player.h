#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "DeckOfCards.h"
#include "Hand.h"
#include "Dice.h"
#include "Dice_rolling.h"

class Strategy;
#include "Strategy.h"
class Country;
#include "Country.h"
class Continent;
#include "Continent.h"

class Player
{

private:
	Hand hand;
	Dice_rolling d1;
	vector <Country*> countries;
	int numOfChosenDices;
	int availableReinforcements;
	Strategy* playerStrategy;

public:
	Player();
	Player(Strategy * initialStrategy);
	~Player();
	void pickCard(DeckOfCards &d);

	void addCountry(Country *c);
	void removeCountry(int);
	bool reinforce(Country*, int);
	int* attack(int);
	bool fortify(Country*, Country*, int);
	int GetNumOfCountry();
	Country* GetCountryInPosition(int position);

	void AddArmytoCountry(Country* c);

	Hand* getHand();
	int GetTotalArmySize();
	int* defend(int);
	int* sort(int*);

	//reinforcements methods
	int GetReinforcementsFromCountries();
	int GetReinforcementsFromContinent();
	int GetReinforcementsFromCards();
	void ReinforcementsCalculation();

	int getAvailableReinforcements();

	bool attackAction(Country*,Country*, int);
	void printCountries();
	bool OwnsContinent();
	int searchCountry(string name);
	void printHand();
	int getNumDices();
	void removeCountryAt(int);

	//Strategy related functions 
	void setStrategy(Strategy* newStrategy);
	Strategy* getStrategy();
	

	vector<Continent*> continents; //un member ici, vraiment?
};
