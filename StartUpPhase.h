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

static class StartUpPhase
{
public:
	static vector<int> OrderOfPlay(int NumOfPlayer);
	static void DistributeCountries(vector<Player*>,MapLoader*);
	static void StartUpPhase::SetUpArmy(vector<Player*>);
	static vector<int>  StartUpPhase::StartGame(vector<Player*>, MapLoader*);
};

