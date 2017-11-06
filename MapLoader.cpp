#include "MapLoader.h"
#include "Continent.h"
#include "Country.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>


MapLoader::MapLoader()
{
	
}

MapLoader::MapLoader(string fn)
{
	fileName = fn;
	fileReader.open(fileName);


	//This part here goes through the text file once to set vector sizes.
	int c = 0;
	string line;
	getline(fileReader, line);
	while (line != "[Continents]")
	{
		getline(fileReader, line);
		//This skips the initial part with the map settings
	}

	while (line != "[Territories]")
	{
		++c;
		getline(fileReader, line);
	}

	continents.resize(c - 2);
	continentPoints.resize(c - 2);
	c = 0; //Now we do the same for the countries.
	int k = 0;

	//This is to repeat the process for countries of each continent
	while (k < continents.size())
	{
		getline(fileReader, line);

		while (line != "")
		{
			++c;
			getline(fileReader, line);
		}

		++k;
	}
	countries.resize(c - 1);

	fileReader.close();

	//Here, I add a little initial test to see if a map file is invalid.
	if (continents.size() == 0 || countries.size() == 0)
	{
		cout << "Invalid map file, terminating program." << endl;
		exit;
	}

	loadSettings();
	loadContinents();
	loadCountries();
}

MapLoader::~MapLoader(void)
{
}

void MapLoader::loadSettings()
{

	cout << "Loading settings..." << endl;
	fileReader.open(fileName);

	//This loads author
	while (fileReader.get() != '=');
	getline(fileReader, author);

	//This loads the image file name
	while (fileReader.get() != '=');
	getline(fileReader, imageName);

	//This loads the wrap
	while (fileReader.get() != '=');
	getline(fileReader, wrap);

	//This loads the scroll
	while (fileReader.get() != '=');
	getline(fileReader, scroll);

	//This loads the warn
	while (fileReader.get() != '=');
	getline(fileReader, warn);

	//Now I do a test to see if all the data is valid.
	if (wrap != "yes" && wrap != "no" || scroll != "horizontal" && scroll != "vertical" && scroll != "none" || warn != "yes" && warn != "no")
	{
		cout << "Invalid map file, terminating program." << endl;
		fileReader.close();
		exit;
	}
}

void MapLoader::loadContinents()
{
	cout << "Loading continents..." << endl;
	string line;
	getline(fileReader, line); //This should be blank
	getline(fileReader, line); //This should be [Continents]
	int i = 0;
	char c = 'a';
	getline(fileReader, line); //North America=5
	while (line != "")
	{
		string contName = "";

		int j = 0;
		c = line[j];
		while (c != '=')
		{
			contName += c;
			++j;
			c = line[j];
		}
		++j;
		continentPoints[i] = stoi(line.substr(j)); //The program will crash here if the map file is invalid. (if the last character of the line is not an int)
		continents[i] = new Continent(contName, 20);
		continents[i]->setReinforcements(continentPoints[i]);

		getline(fileReader, line);
		++i;
	}

	//Because I made sure that the continents were valid in the constructor, I don't need to worry about it here.
}

void MapLoader::splitCountries(vector<Player*> players)
{
	int size = players.size();
	for (int i = 0; i < countries.size(); i++) {

			players.at(i % size)->addCountry(countries.at(i));	
			countries.at(i)->setOwner(players.at(i % size));
			
	}	

}

vector<string*> MapLoader::getCountriesNames()
{
	vector<string*> s;
	for (int i = 0; i < countries.size(); i++)
	{
		s.push_back(new string(countries[i]->getName()));
	}

	return s;
}

Player* MapLoader::getOwnerOfCountry(string name)
{
	Player * p = NULL;
	for (int i = 0; i < countries.size(); i++) {
		if (name == countries[i]->getName()) {
			p = countries[i]->getOwner();
		}
	}
	return p;
}


vector<Country*> MapLoader::getCountries()
{
	return countries;
}


void MapLoader::loadCountries()
{
	cout << "Loading countries..." << endl;
	string line = "";
	getline(fileReader, line); //Line should be == [Territories], I only use this to put the fileReader at the right place in the .map file
	int adjacentCountriesStart;

	for (int i = 0; i < countries.size(); ++i)
	{
		int j = 0;
		char c = 'a';
		getline(fileReader, line);
		string countryName = "";

		if (line == "") //This is for when the countries change continents, since there is a blank line between each.
		{
			getline(fileReader, line);
		}

		while (c != ',') //name of the country
		{
			c = line[j];
			countryName += c;
			++j;
		}

		countryName.pop_back(); //to remove the comma at the end.

		c = 'a';
		while (c != ',') //coordinate (not used for now)
		{
			c = line[j];
			++j;
		}

		c = 'a';
		while (c != ',') //coordinate (not used for now)
		{
			c = line[j];
			++j;
		}

		c = 'a';
		while (c != ',') //continent
		{
			c = line[j];
			++j;
		}

		adjacentCountriesStart = j;
		int numberAdjacentTerritories = 0;
		c = 'a';
		for (int k = adjacentCountriesStart; k < line.length(); ++k)
		{
			c = line[k];

			if (c == ',')
			{
				++numberAdjacentTerritories;
			}
		}

		++numberAdjacentTerritories; //because the number of adjacent territories will always be the number of commas + 1.
		vector <Country*> adjacent;
		adjacent.resize(numberAdjacentTerritories);

		for (int k = 0; k < numberAdjacentTerritories; ++k)
		{
			string adjacentCountryName = "";
			c = line[j];
			while (c != ',')
			{
				adjacentCountryName += c;

				++j;

				if (j == line.length())
				{
					break;
				}

				c = line[j];
			}

			adjacent[k] = new Country(adjacentCountryName);

			++j;
		}

		countries[i] = new Country(countryName, adjacent);



	}

	fileReader.close();
}

void MapLoader::displayMap()
{
	cout << "Here are the current settings for this map: " << endl;
	cout << "\nFile name: " << fileName << "\nAuthor: " << author << "\nImage: " << imageName << "\nWrap: " << wrap << "\nScroll: " << scroll << "\nWarn: " << warn << endl;
	cout << "\nHere are the continents for this map: " << endl;

	for (int i = 0; i < continents.size(); ++i)
	{
		cout << continents[i]->getContName() << endl;
	}

	cout << "\nHere is each country with its adjacent countries: " << endl;

	for (int i = 0; i < countries.size(); ++i)
	{
		cout << countries[i]->getName();
		cout << "\tAdjacent: ";

		for (int j = 0; j < countries[i]->getAdjacencySize(); ++j)
		{
			cout << countries[i]->getAdjacencyAt(j)->getName() << " ";
		}

		cout << "\n" << endl;
	}
}

void MapLoader::SetUpArmy(vector<Player*> Players)
{
	int NumOfPlayers = Players.size();
	int StartArmySize;

	switch (NumOfPlayers)
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

	for (int i = 0; i < NumOfPlayers; i++)
	{
		int tempArmy = StartArmySize;
		for (int a = 0; a < StartArmySize; a = a + Players[i]->GetNumOfCountry())
		{
			for (int c = 0; c < Players[i]->GetNumOfCountry(); c++)
			{
				if (tempArmy > 0)
				{
					Players[i]->AddArmytoCountry(Players[i]->GetCountryInPosition(c));
					tempArmy--;
				}
			}
		}
	}
}

void MapLoader::printContinent() {
	cout << continents.size() << endl;
	for (int i = 0; i < continents.size(); i++) {
		cout << continents[i]->getReinforcements() << endl;


	}

}
