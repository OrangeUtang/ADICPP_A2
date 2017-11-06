#include "Continent.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;


Continent::Continent(string aName, int aNumMem)
{
	name = aName;
	numberMembers = aNumMem;
	countryMembers.resize(aNumMem);
	reinforcements = 0;
	adjacentContinent;

}


Continent::~Continent()
{
}

string Continent::getContName()
{
	return name;
}

void Continent::setContName(string aName)
{
	name = aName;
}

int Continent::getNumberMembers()
{
	return numberMembers;
}

void Continent::setNumberMembers(int x)
{
	numberMembers = x;
}

Country* Continent::getCountryMembersAt(int x)
{
	return countryMembers.at(x);
}
void Continent::setCountryMembersAt(int x, Country* aCountry)
{
	countryMembers.at(x) = aCountry;
}

int Continent::getReinforcements()
{
	return reinforcements;
}

void Continent::setReinforcements(int x)
{
	reinforcements = x;
}

Continent* Continent::getAdjacentContinentAt(int x)
{
	return adjacentContinent.at(x);
}
void Continent::setAdjacentContinentAt(int x, Continent* aCont)
{
	adjacentContinent.at(x) = aCont;
}