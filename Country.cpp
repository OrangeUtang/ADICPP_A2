#include "Country.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Country::Country(string aName, int aNumber)
{
	name = aName;
	army = 0;
	numberAdjacency = aNumber;
	adjacency.resize(aNumber);
	continent;
	linked = false;
	owner = NULL;
}

Country::Country(string aName, vector <Country*> aVector)
{
	name = aName;
	army = 0;
	numberAdjacency = aVector.size();
	adjacency = aVector;
	continent;
	linked = false;
	owner = NULL;
}

Country::Country(string aName)
{
	name = aName;
	army = 0;
	numberAdjacency = 0;
	adjacency;
	continent;
	linked = false;
	owner = NULL;
}


Country::~Country()
{

}

string Country::getName()
{
	return name;
}

void Country::setName(string aName)
{
	name = aName;
}

int Country::getArmy()
{
	return army;
}

void Country::setArmy(int aNumber)
{
	army = aNumber;
}

int Country::getNumberAdjacency()
{
	return numberAdjacency;
}

void Country::setNumberAdjacency(int x)
{
	numberAdjacency = x;
}


Country* Country::getAdjacencyAt(int x)
{
	return adjacency.at(x);
}

bool Country::isAdjacent(Country* aCountry)
{
	for (int i = 0; i < numberAdjacency; i++)
	{
		if (getAdjacencyAt(i) == aCountry)
			return true;
	}

	return false;
}

void Country::printAdjacents()
{
	for (int i = 0; i < numberAdjacency; i++)
	{
		cout << getAdjacencyAt(i)->getName() << endl;
	}
}

void Country::setAdjacency(vector <Country*> aVector)
{
	numberAdjacency = aVector.size();
	adjacency.resize(aVector.size());
	adjacency = aVector;
}

void Country::setAdjacencyAt(int x, Country* aNode)
{
	adjacency.at(x) = aNode;
}

Continent* Country::getContinent()
{
	return continent;
}

void Country::setContinent(Continent* aCont)
{
	continent = aCont;
}

bool Country::isLinked()
{
	return linked;
}

void Country::setLinked(bool aBool)
{
	linked = aBool;
}

Player* Country::getOwner()
{
	return owner;
}

void Country::setOwner(Player* aPlayer)
{
	owner = aPlayer;
}

int Country::getAdjacencySize()
{
	return adjacency.size();
}