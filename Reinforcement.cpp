#include "Reinforcement.h"
#include "Cards.h"
#include "Continent.h"
#include "Country.h"
#include "DeckOfCards.h"
#include "Dice.h"
#include "Dice_rolling.h"
#include "Hand.h"
#include "MapChecker.h"
#include "MapLoader.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include "GameStarter.h"
#include <random>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

//Reinforcement is a static class that can be called by a player to receive the correct number of soldiers
//to be placed on the map. For the demo, it also places them semi randomly on the map.

int GetReinforcementsFromCountries(Player* p)
{
	if ((int)(p->GetNumOfCountry() / 3) > 3)
		return (int)(p->GetNumOfCountry() / 3);
	else
		return 3;
		//Returns the highest number between 3 and the number of countries / 3
}

int GetReinforcementsFromContinent(Player* player)			//Methods that checks if the player owns a continent and how much is the continent worth
{
	int tempArmy = 0;
		if (player->OwnsContinent())
		{
			for (int i = 0; i < player->continents.size(); i++)
			{
				tempArmy += player->continents[i]->getReinforcements();	
			}
		}
	return tempArmy;
}

int GetReinforcementsFromCards(Player* player)
{
	return player->getHand()->Exchange();				//Method that uses the Exchange method from hand to receive additionnal soldiers when possible
}

void Reinforcement::ReinforcementsPhase(Player* player)			//Main method of the function that will call all other methods and wil pace the soldiers on the countries
{
	int Army = 0;
	Army = Army + GetReinforcementsFromCountries(player) + GetReinforcementsFromContinent(player) + GetReinforcementsFromCards(player); //Calculates the reinforcments
	while (true)
	{
		for (int c = 0; c < player->GetNumOfCountry(); c++)	//For all countries this player has
		{
			if (Army <= 0)
				break;
			player->AddArmytoCountry(player->GetCountryInPosition(c));  //Add a soldier to it
			Army--;
		}
		if (Army <= 0)						//When all reinforcements are placed, break out of the loop
			break;
	}	
}


