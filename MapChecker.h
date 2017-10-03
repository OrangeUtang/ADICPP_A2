#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Country.h"
#include "Continent.h"

using namespace std;

class MapChecker
{
private:
	vector <Country*> countryVector;
	int numbrCountry;
	vector <Continent*> continentVector;
	int numbrContinent;

public:
	MapChecker(vector <Country*>, vector <Continent*>);
	~MapChecker();

	bool isMapTwoWay();
	bool isMapLinked();
	bool areContinentLinked(int);
	bool haveDuplicateCountry();
	bool haveDuplicateContinent();
	bool haveDualBelonging();
	bool isMapCoherent(int);
};

