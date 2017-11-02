#pragma once
#include <string>
#include "MapLoader.h"
#include "Player.h"


using namespace std;

class GameStarter
{
private : 

	MapLoader *Map;
	vector<Player*> players;
	DeckOfCards deck;


public:
	GameStarter();
	~GameStarter();
	void createPlayers();

	void printPlayerCountries();

	int getNumOfPlayers();

	void attackPhase();



};

