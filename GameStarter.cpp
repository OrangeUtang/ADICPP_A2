#include "GameStarter.h"
#include "MapLoader.h"
#include <iostream>
#include "StartUpPhase.h"

using namespace std;


GameStarter::GameStarter()
{
	int map;
	cout << "Please select a map from the following maps : " << endl <<
		"1. World" << endl <<
		"2. Canada" << endl <<
		"3. Asia " << endl <<
		"4. Australia" << endl <<
		"5. Africa " << endl;

	cin >> map;

	switch (map) {
	case 1: Map = new MapLoader("World.map"); break;
	case 2: Map = new MapLoader("Canada.map"); break;
	case 3: Map = new MapLoader("Asia.map"); break;
	case 4: Map = new MapLoader("Australia.map"); break;
	case 5: Map = new MapLoader("Africa.map"); break;
	default: Map = new MapLoader("World.map"); break;
	}

	vector<string*> s = Map->getCountriesNames();
	deck = DeckOfCards(s, s.size());
	
}


GameStarter::~GameStarter()
{
}


void GameStarter::createPlayers()
{
	
	int num;
	cout << "How Many players will be playing? (2-6) ";
	cin >> num;
	if (num < 2)
	{
		cout << "cant be lower than 2. Will be set to 2." << endl;
		num = 2;
	}
	if (num > 6)
	{
		cout << "cant be higher than 6. Will be set to 6." << endl;
		num = 6;
	}
	for (int i = 0; i < num; i++)
	{
		Player *p = new Player;
		players.push_back(p);
	}
	cout << endl;
	players.at(1)->printHand();
	cout << endl;
	//Split countries to each players and set army on every country
	StartUpPhase::StartGame(players, Map);

}

void GameStarter::printPlayerCountries(){
	
	for (int i = 0; i < players.size(); i++) {
		cout << endl << "PLAYER #" << i+1 << " COUNTRIES:" << endl << endl;
		players.at(i)->printCountries();
	
	}

}

int GameStarter::getNumOfPlayers() {

	return players.size();

}

/* This function simulate an attack phase with 2 players. 
	The winner of the battle win the Country .*/

void GameStarter::attackPhase() {

	int att = -1;
	while (att < 0 || att >= players.size()) {
		cout << "Which player is attacking ? " << endl;
		cin >> att;
		att -= 1;
	}

	cout << "PLAYER " << att + 1 << " IS ATTACKING " << endl;

	char c;
	string myCountry, advCountry;
	int numArmiesatt, numArmiesDef, numDiceAtt, numDiceDef, defLoc, numOfLossArmyAtt=0, numOfLossArmyDef=0;
	Country* attCountry, *defCountry;
	Player *p;
	int* attD, * defD;
	cout << endl<<"Do you want to attack ? y/n" << endl;
	cin >> c;

	//Player still want to attack or not
	while (c == 'y') {

		do {

			cout << "Select one of your countries to attack from : ";
			cin >> myCountry;
			int attLoc = players[att]->searchCountry(myCountry);
			attCountry = players[att]->GetCountryInPosition(attLoc);
			attCountry->printAdjacents();


			cout << "Select the country you want to attack : ";
			cin >> advCountry;
				//get the owner of the country 
				p = Map->getOwnerOfCountry(advCountry);
				defLoc = p->searchCountry(advCountry);
				defCountry = p->GetCountryInPosition(defLoc);

		} while (!(attCountry->isAdjacent(defCountry)));
		
		// Getting the number of army on each country before the battle 
		numArmiesatt = attCountry->getArmy();
		numArmiesDef = defCountry->getArmy();

		cout << endl << "Army on attacking country : " << numArmiesatt << endl;
		cout <<"Army on Defending country : " << numArmiesDef << endl;
		attD = players[att]->attack(numArmiesatt);
		defD = p->defend(numArmiesDef);

		numDiceAtt = players[att]->getNumDices();
		numDiceDef = p->getNumDices();

		//Comparing the Dices 
		if (numDiceAtt >= 2 && numDiceDef == 2) {

			cout << endl<< "Comparing Dices : " << endl << attD[0] << " with " << defD[0] << endl
				<< attD[1] << " with " << defD[1] << endl;
			if (attD[0] > defD[0])
			{
				numOfLossArmyDef++;
			}
			if (attD[1] > defD[1])
			{
				numOfLossArmyDef++;
			}
			if (attD[0] <= defD[0])
			{
				numOfLossArmyAtt++;
			}
			if (attD[1] <= defD[1])
			{
				numOfLossArmyAtt++;
			}
			
			
		}

		if (numDiceAtt >= 1 && numDiceDef == 1) {

			cout << endl << "Comparing Dices : " << endl << attD[0] << " with " << defD[0];

			if (attD[0] > defD[0])
			{
				numOfLossArmyDef++;
			}
			if (attD[0] <= defD[0])
			{
				numOfLossArmyAtt++;
			}
			
			
		}

		//If defending player still have amies, continue
		if (defCountry->getArmy() - numOfLossArmyDef > 0) {
			int numLeftArmyDef = defCountry->getArmy() - numOfLossArmyDef;
			int numLeftArmyAtt = attCountry->getArmy() - numOfLossArmyAtt;
			defCountry->setArmy(numLeftArmyDef);
			attCountry->setArmy(numLeftArmyAtt);
			if (attCountry->getArmy() <= 1) {
			
				cout << endl << "Not Enough Armies to continue" << endl;
				cout << "End of attack phase." << endl;
				c = 'n';
			}
			numArmiesDef = defCountry->getArmy();
		}

		//Else defending player lose his country, attacking player win the country
		else {

			cout << endl << "The attacker won the country" << endl;

			players[att]->addCountry(defCountry);
			p -> removeCountry(defLoc);
			numArmiesDef = 0;
			int newNumArmy;
			cout << "How many armies do you want to put on new Country?" << endl;
			do
			{
				cin >> newNumArmy;

			} while (newNumArmy > (attCountry->getArmy()) - 1 || newNumArmy < 0);

				attCountry->setArmy(attCountry->getArmy()- newNumArmy);

			}

		numArmiesatt = attCountry->getArmy();
		
		// Getting the number of army on each country After the battle 
		cout << "Army on attacking country : " << numArmiesatt << endl;
		cout << "Army on Defending country : " << numArmiesDef << endl;

		numOfLossArmyDef = 0, numOfLossArmyAtt=0;

		if (c == 'y') {
			//redo loop until user press n 
			cout << "Do you want to attack again ? y/n" << endl;
			cin >> c;
		}


	}

	cout << "End of attack phase." << endl;
	

}







