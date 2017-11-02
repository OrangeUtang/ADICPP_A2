#pragma once

#include "Country.h"
#include "Continent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class MapLoader
{
private:

	string fileName;
	ifstream fileReader;
	
	string author;
	string imageName;
	string wrap;
	string scroll;
	string warn;

	vector<Country*> countries;
	vector<Continent*> continents;
	vector<int> continentPoints;

public:
	MapLoader(string);
	~MapLoader(void);

	void loadSettings();
	void loadCountries();
	void loadContinents();

	void displayMap();
	vector<Country*> getCountries();
};

