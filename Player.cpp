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

Player::Player(Strategy* initialStrategy)
{
	playerStrategy = initialStrategy;
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


bool Player::reinforce(Country* aCountry, int numbrReinforcements)
{
	//verify if there is enough reinforcements availables to proceed.
	if (availableReinforcements < numbrReinforcements)
	{
		cout << "Insufficient Reinforcements" << endl;
		return false;
	}

	//verify if player actually own the country it tries to reinforces
	if (aCountry->getOwner() != this)
	{
		cout << aCountry->getName() + " does not belong to the right player" << endl;
		return false;
	}

	//if valid, reinforce

	

	aCountry->setArmy(aCountry->getArmy() + numbrReinforcements);
	availableReinforcements = availableReinforcements - numbrReinforcements;

	cout << "player reinforces" << numbrReinforcements << " to " << aCountry->getName() << endl;
 
	return true;

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



//-------------REINFORCMENT RELATED STUFF------------------------------------------
//Reinforcement is a static class that can be called by a player to receive the correct number of soldiers
//to be placed on the map. For the demo, it also places them semi randomly on the map.

int Player::GetReinforcementsFromCountries()
{
	if ((int)(GetNumOfCountry() / 3) > 3)
		return (int)(GetNumOfCountry() / 3);
	else
		return 3;
	//Returns the highest number between 3 and the number of countries / 3
}

int Player::GetReinforcementsFromContinent()			//Methods that checks if the player owns a continent and how much is the continent worth
{
	int tempArmy = 0;
	if (OwnsContinent())
	{
		for (int i = 0; i < continents.size(); i++)
		{
			tempArmy += continents[i]->getReinforcements();
		}
	}
	return tempArmy;
}

int Player::GetReinforcementsFromCards()
{
	return getHand()->Exchange();				//Method that uses the Exchange method from hand to receive additionnal soldiers when possible
}

void Player::ReinforcementsCalculation()			//Main method of the function that will call all other methods and wil pace the soldiers on the countries
{
	int army = 0;
	army = army + GetReinforcementsFromCountries() + GetReinforcementsFromContinent() + GetReinforcementsFromCards(); //Calculates the reinforcments
	availableReinforcements = army;
	
}

int Player::getAvailableReinforcements()
{
	return availableReinforcements;
}


bool Player::attackAction(Country* attackingCountry ,Country* attackedCountry, int numbrDices)
{
	bool success = false;

	cout << "A player tries to attack from " << attackingCountry->getName() << " to " << attackedCountry->getName() << endl;

	//if attaking countries does not belong to attacking country, return false.
	if (attackingCountry->getOwner() != this)
	{
		cout << attackingCountry->getName() + " does not belong to the right player" << endl;
		return false;
	}

	//if attacked country belongs to the attacker return false.
	if (attackedCountry->getOwner() == this)
	{
		cout << "the player can't attack his own country, " + attackedCountry->getName() << endl;
		return false;
	}

	//if the attacking and defending countries are adjacent, set success to true.
	for (int i = 0; i < attackingCountry->getNumberAdjacency(); i++)
	{
		if (attackingCountry->getAdjacencyAt(i) == attackedCountry)
		{
			success = true;
		}
	}

	// if succes is false (and countries are not adjacent) return false.
	if (success == false)
	{
		cout << attackedCountry->getName() + " is not adjacent to "+ attackingCountry->getName() +" , can't proceed" << endl;
		return false;
	}

	//if number of dices is valid
	if (numbrDices > 3)
		return false;

	//if number of dice is greater or equal to the number of attacking armies minus 1, return false.
	if (numbrDices > attackingCountry->getArmy() - 1)
		return false;


	//declaring new variables that makes the code more readable.
	int* attD = attack(numbrDices);
	int* defD = attackedCountry->getOwner()->defend(attackedCountry->getArmy());      // defend strategy needed?


	//dicerolling comparison when the defender uses 2 different.
	if (getNumDices() >= 2 && attackedCountry->getOwner()->getNumDices() == 2)
	{

		cout << endl << "Comparing Dices : " << endl << attD[0] << " with " << defD[0] << endl << attD[1] << " with " << defD[1] << endl;

		if (attD[0] > defD[0])
		{
			attackedCountry->setArmy(attackedCountry->getArmy() - 1);
			cout << attackedCountry->getName() + " loses 1 army" << endl;
		}

		if (attD[1] > defD[1])
		{
			attackedCountry->setArmy(attackedCountry->getArmy() - 1);
			cout << attackedCountry->getName() + " loses 1 army" << endl;
		}

		if (attD[0] <= defD[0])
		{
			attackingCountry->setArmy(attackingCountry->getArmy() - 1);
			cout << attackingCountry->getName() + " loses 1 Army" << endl;
		}

		if (attD[1] <= defD[1])
		{
			attackingCountry->setArmy(attackingCountry->getArmy() - 1);
			cout << attackingCountry->getName() + " loses 1 Army" << endl;
		}

	}


	//Dice rolling comparison when the defender only uses one dice.
	if (getNumDices() >= 1 && attackedCountry->getOwner()->getNumDices() == 1) {

		cout << endl << "Comparing Dices : " << endl << attD[0] << " with " << defD[0] << endl;

		if (attD[0] > defD[0])
		{
			attackedCountry->setArmy(attackedCountry->getArmy() - 1);
			cout << attackedCountry->getName() + " loses 1 army" << endl;
		}
		if (attD[0] <= defD[0])
		{
			attackingCountry->setArmy(attackingCountry->getArmy() - 1);
			cout << attackingCountry->getName() + " loses 1 Army" << endl;
		}
	}

	//case where attacker conquer the country.
	if (attackedCountry->getArmy() <= 0)
	{
		//making sure army does not go in the negative .
		attackedCountry->setArmy(0);


		//removing country from previous owner country list.
		for (int i = 0; i < attackedCountry->getOwner()->GetNumOfCountry(); i++)
		{
			if (attackedCountry->getOwner()->GetCountryInPosition(i) == attackedCountry)
			{
				attackedCountry->getOwner()->removeCountryAt(i);
			}
		}

		//changing ownership of conquered country in both the country and in the player array.
		attackedCountry->setOwner(this);
		addCountry(attackedCountry);

		//transfering minimum number of armies from attacker to conquered country.
		attackingCountry->setArmy(attackingCountry->getArmy() - numOfChosenDices);
		attackedCountry->setArmy(attackedCountry->getArmy() + numOfChosenDices);

		cout << attackedCountry->getName() + " now belongs to the attacking player." << endl;

		//return true since the attack has been completed.
		return true;
	}
	//return true since the attack has been made.
	return true;
}

//method used to fortify at the end of a turn.
bool Player::fortify(Country* initialC, Country* destinationC, int armies)
{
	bool success = false;

	cout << "The player tries to fortify " << armies << " armies from " << initialC->getName() << " to " << destinationC->getName() << endl;

	//checks if the owner of the first country is the calling player.
	if (initialC->getOwner() != this)
	{
		cout << "initial Country does not belong to the right player" << endl;
		return false;
	}

	//checks if the owner of second country is the calling player.
	if (destinationC->getOwner() != this)
	{
		cout << "destination Country does not belong to the right player " << endl;
		return false;
	}


	//checks if the second country is adjacent to the first one.
	for (int i = 0; i < initialC->getNumberAdjacency(); i++)
	{
		if (initialC->getAdjacencyAt(i) == destinationC)
		{
			success = true;
		}
	}

	//return false if they.
	if (success == false)
	{
		cout << "destination is not adjacent, can't proceed" << endl;
		return false;
	}


	//check if initial country has enough armies to fortify as much unit as what is required.
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
			cout << "Country " << i << " : " << countries.at(i)->getName() << "   Army: " << countries.at(i)->getArmy() << endl;
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

void Player::removeCountryAt(int i)
{
	countries.at(i) = null;
	countries.erase(countries.begin() + i);
}

void Player::setStrategy(Strategy* newStrategy)
{
	playerStrategy = newStrategy;
}

Strategy* Player::getStrategy()
{
	return  playerStrategy;
}
