#pragma once

class Continent;
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;


class Country
{
private:
	string name;
	int army;
	int numberAdjacency;
	//vector <Country*> adjacency;
	Continent* continent;
	bool linked;
	Player* owner;




public:
	vector <Country*> adjacency;
	Country(string, int);
	Country(string, vector <Country*>);
	Country(string);
	~Country();

	string getName();
	void setName(string);

	int getArmy();
	void setArmy(int);

	int getNumberAdjacency();
	void setNumberAdjacency(int);

	Country* getAdjacencyAt(int);
	bool isAdjacent(Country * aCountry);
	void setAdjacencyAt(int, Country*);

	void setAdjacency(vector <Country*>);

	Continent* getContinent();
	void setContinent(Continent*);

	bool isLinked();
	void setLinked(bool);

	Player* getOwner();
	void setOwner(Player*);

	void printAdjacents();


};

