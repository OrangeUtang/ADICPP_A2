#include "Player.h"
#include "Country.h"
#include "Hand.h"
#include "Reinforcement.h" 
#include <iostream>
#include <vector>
#include <string>

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

void Player::addCountry(Country *c) 

{

	countries.push_back(c);

}

void Player::removeCountry(int x) 

{

	countries.at(x)->~Country();

}


void Player::reinforce()
{
	cout << "The player Reinforeces!" << endl;
}




int* Player::attack(int numArmies)
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



int* Player::defend(int numArmies)
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

//method used to fortify at the end of a turn
bool Player::fortify(Country* initialC, Country* destinationC, int armies)
{
	bool success = false;

	cout << "The player tries to fortify " << armies << " armies from " << initialC->getName() << " to " << destinationC->getName() << endl;

	//checks if the owner of the first country is the calling player
	if (initialC->getOwner() != this)
	{
		cout << "initial Country does not belong to the right player" << endl;
		return false;
	}

	//checks if the owner of second country is the calling player
	if (destinationC->getOwner() != this)
	{
		cout << "destination Country does not belong to the right player " << endl;
		return false;
	}


	//checks if the second country is adjacent to the first one
	for (int i = 0; i < initialC->getNumberAdjacency(); i++)
	{
		if (initialC->getAdjacencyAt(i) == destinationC)
		{
			success = true;
		}
	}

	//return false if they 
	if (success == false)
	{
		cout << "destination is not adjacent, can't proceed" << endl;
		return false;
	}


	//check if initial country has enough armies to fortify as much unit as what is required
	if (armies >= initialC->getArmy())
	{
		cout << "Insuficient army in this country, need to leave a minimum of 1 army per country" << endl;
		return false;
	}


	// if the code reach this point, it means the move is valid, proceeds by removing armies from starting position and adds them to ending position.
	initialC->setArmy(initialC->getArmy() - armies);
	destinationC->setArmy(destinationC->getArmy() + armies);
	cout << "The player Fortities " << armies << " armies from " << initialC->getName() << " to " << destinationC->getName() << endl;
	return true;

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

Hand* Player::getHand()
{
	return &hand;
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
			cout << "Country " << i << " : " << countries.at(i)->getName() << endl;
		}
	}

}

bool Player::OwnsContinent()
{
	if (continents.size() > 0)
		return true;
	else
		return false;
}




int Player::searchCountry(string name) {

	for (int i = 0; i < countries.size(); i++) {

		if (countries.at(i)->getName() == name) { return i; }

	}

	cout << "You don't possess this country" << endl;

	return 0;

}



void Player::printHand()
{
	hand.PrintHand();
}

int Player::getNumDices()
{
	return numOfChosenDices;
}

