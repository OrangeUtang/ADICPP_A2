#include "StartUpPhase.h"
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

//The startUpPhaseis a static class that will be used to assign the correct order of play, assign the coutries to the players and 
//places the correct number of soldiers on the map.

vector<int>  StartUpPhase::OrderOfPlay(int NumOfPlayer) 	//Function that dertermines randomly the order of play of the player 
{
	bool IsIn = false;
	int ran;
	srand(time(0));						//Sets the seed of the random
	vector<int> order;
	while (true)						//Loops until Breaks out
	{
		ran = rand() % NumOfPlayer + 1;			//Returns a number between 1 and the number of player
		for (int y = 0; y < order.size(); y++)		//Loop that checks if the random number as already been assigned in the order array
		{
			if (order[y] == ran)
				IsIn = true;
		}

		if (!IsIn)
			order.push_back(ran);			//If not already in the array, adds it

		IsIn = false;
		if (order.size() == NumOfPlayer)
			break;					//When all players have been added, break out of the loop
	}
	return order;
}

void StartUpPhase::DistributeCountries(vector<Player*> Players, MapLoader *M)
{
	vector<Country*> Countries = M->getCountries();

	for (int i = 0; i < Countries.size(); i++)
	{
		Players[i % Players.size()]->addCountry(Countries[i]);	//For each country, distribute it randomy for all the players
	}
}

void StartUpPhase::SetUpArmy(vector<Player*> Players)
{
	int NumOfPlayers = Players.size();			//Checks the number of players in the game
	int StartArmySize;

	switch (NumOfPlayers)					//Assigns the correct number of soldiers per player, dertermined by the number of players
	{
	case 2: StartArmySize = 40;
		break;
	case 3: StartArmySize = 35;
		break;
	case 4: StartArmySize = 30;
		break;
	case 5: StartArmySize = 25;
		break;
	case 6: StartArmySize = 20;
		break;
	default: StartArmySize = 30;
	}

	for (int i = 0; i < NumOfPlayers; i++)			//Places, for each player, all the soldiers accross the countries this player owns.
	{
		int tempArmy = StartArmySize;
		for (int a = 0; a < StartArmySize; a = a + Players[i]->GetNumOfCountry())
		{
			for (int c = 0; c < Players[i]->GetNumOfCountry(); c++)
			{
				if (tempArmy > 0)
				{
					Players[i]->AddArmytoCountry(Players[i]->GetCountryInPosition(c)); //Add 1 soldier to the country
					tempArmy--;
				}
			}
		}
	}
}

vector<int>  StartUpPhase::StartGame(vector<Player*> Players, MapLoader *M)	//Automated methods that uses all methods above without having to call them seperatly
{
	cout << "--- GAME START UP ---" << endl;
	vector<int> order = StartUpPhase::OrderOfPlay(Players.size());
	StartUpPhase::DistributeCountries(Players,M);
	StartUpPhase::SetUpArmy(Players);
	return order;
}
