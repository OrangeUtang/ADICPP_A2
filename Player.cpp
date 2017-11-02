#include "Player.h"
#include "Country.h"
#include "Hand.h"
#include <iostream>
#include <vector>
#include <string>
#include "Reinforcement.h" 

static Country* null = new Country("NULL", 0);
Hand hand;

Player::Player(void)
{

	vector<Country*> countries;

}

Player::~Player(void)
{

}

void Player::pickCard(DeckOfCards &deck)
{
	hand.AddCardToHand(deck.Draw());
	
}

void Player::addCountry(Country *c) {

	countries.push_back(c);

}

void Player::Reinforce()
{
	cout << "The player Reinforeces!" << endl;
	Reinforcement::ReinforcementsPhase(this);
}

void Player::removeCountry(int x) {

	countries.at(x) = null;

}

Hand* Player::getHand()
{
	return &hand;
}


int* Player::Attack(int numArmies)
{

	int *att;

	if (numArmies < 3)
	{
		numOfChosenDices = d1.roll(numArmies);
	}

	else numOfChosenDices = d1.roll(3);

	att = d1.getContainer();

	att = sort(att);

	return att;
}



int* Player::Defend(int numArmies)
{

	int *def;

	if (numArmies < 2)
	{
		numOfChosenDices = d1.roll(numArmies);
	}

	else numOfChosenDices = d1.roll(2);

	def = d1.getContainer();

	def = sort(def);

	return def;

}


int * Player::sort(int * ar)
{
	int temp;
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (ar[i]>ar[j])
			{
				temp = ar[i];
				ar[i] = ar[j];
				ar[j] = temp;
			}
		}
	}
	return ar;
}


void Player::Fortify()
{
	cout << "The player Fortities!" << endl;
}


int Player::GetNumOfCountry()
{
	return countries.size();
}


Country* Player::GetCountryInPosition(int position)
{
	return countries[position];
}

void Player::AddArmytoCountry(Country* c)
{
	for (int i = 0; i < countries.size(); i++)
	{
		if (countries[i]->getName() == (c->getName()))
			countries[i]->setArmy(countries[i]->getArmy() + 1);
	}
}

int Player::GetTotalArmySize()
{
	int ArmySize = 0;
	for (int i = 0; i < countries.size(); i++)
	{
		ArmySize = ArmySize + countries[i]->getArmy();
	}
	return ArmySize;
}

void Player::printCountries() {


	if (countries.size() == 0) {
		cout << "Player has no owned countries at this time ";
	}

	else {

		for (int i = 0; i < countries.size(); i++)
		{
			if (countries.at(i)->getName() == "NULL") {

			}

			else{
				cout << countries.at(i)->getName() << endl;
			}
		}
	}

}


int Player::searchCountry(string name) {

	for (int i = 0; i < countries.size(); i++) {
	
		if (countries.at(i)->getName() == name) { return i; }

	}

	cout << "You don't possess this country" << endl;

	return 0;

}

bool Player::OwnsContinent()
{
	if (continents.size() > 0)
		return true;
	else
		return false;
}



void Player::printHand()
{
		hand.PrintHand();
}

int Player::getNumDices()
{
	return numOfChosenDices;
}
