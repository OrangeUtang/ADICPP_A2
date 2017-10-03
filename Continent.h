#pragma once

class Country;
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Continent
{
private:
	string name;
	int numberMembers;
	vector <Country*> countryMembers;
	int reinforcements;
	vector <Continent*> adjacentContinent;

public:
	Continent(string, int);
	~Continent();

	string getContName();
	void setContName(string);

	int getNumberMembers();
	void setNumberMembers(int);

	Country* getCountryMembersAt(int);
	void setCountryMembersAt(int, Country*);

	int getReinforcements();
	void setReinforcements(int);

	Continent* getAdjacentContinentAt(int);
	void setAdjacentContinentAt(int, Continent*);


};

