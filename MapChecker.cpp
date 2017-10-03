#include "MapChecker.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;


MapChecker::MapChecker(vector <Country*> aCountVec, vector <Continent*> aContVec)
{
	countryVector = aCountVec;
	numbrCountry = countryVector.size();
	continentVector = aContVec;
	numbrContinent = continentVector.size();
}


MapChecker::~MapChecker()
{

}


bool MapChecker::isMapTwoWay()
{
	for (int i = 0; i < numbrCountry; i++) //cycle through all countries
	{
		Country* tempCountry = countryVector.at(i);

		for (int j = 0; j < (tempCountry->getNumberAdjacency()); j++) //Cycle through all adjacent countries of tempCountry.
		{
			Country* tempCountry2 = tempCountry->getAdjacencyAt(j);

			for (int k = 0; k < tempCountry->getAdjacencyAt(j)->getNumberAdjacency(); k++) //cycles through all adjacency's adjacency making sure the relation is reciprocal.
			{
				Country* tempCountry3 = tempCountry->getAdjacencyAt(j)->getAdjacencyAt(k);

				if (tempCountry == tempCountry->getAdjacencyAt(j)->getAdjacencyAt(k)) // if adjacent at j contain an adjaccent at k whom have the same adress as temp, go to next adjacent.
				{
					break;
				}

				else if (k == (tempCountry->getAdjacencyAt(j)->getNumberAdjacency()) - 1) // if none of the adjacent's country adjacents is the original country, the map is not 2 way.
				{
					cout << "Missing path from " + tempCountry->getAdjacencyAt(j)->getName() + " to " + tempCountry->getName() << endl;
					tempCountry = NULL;
					tempCountry2 = NULL;
					tempCountry3 = NULL;
					return false;
				}
				tempCountry3 = NULL;
			}
			tempCountry2 = NULL;
		}
		tempCountry = NULL;
	}

	cout << "All path are two way" << endl; //if code reach this point it means that all paths are 2 way for the whole country list;
	return true;
}


bool MapChecker::isMapLinked() // makes sure that all countries form a connected graph
{
	countryVector.at(0)->setLinked(true); // set first data as "linked"
	int linkedCounter = 1; // set a counter that add to himself everytime a country is linked to the "linked graph"
	int initCounter = 0;

	while (initCounter < linkedCounter) // if linkedCounter keeps growing, keep going
	{
		initCounter = linkedCounter; //update inital counter
		for (int i = 0; i < numbrCountry; i++) // Cycle through all the country nodes
		{
			if (countryVector.at(i)->isLinked()) // if country is linked -----------------------------
			{
				for (int j = 0; j < countryVector.at(i)->getNumberAdjacency(); j++) // for all the adjacent country to the previous country
				{
					if (countryVector.at(i)->getAdjacencyAt(j)->isLinked() == false) // if they are not linked
					{
						countryVector.at(i)->getAdjacencyAt(j)->setLinked(true); // link them
						linkedCounter++;										// add to the counter

						if (linkedCounter == numbrCountry)						//if counter is equal to the number of country exit function
						{
							cout << "all countries are linked" << endl;
							return true;
						}
					}
				}
			}

			else if (!countryVector.at(i)->isLinked()) // if country is not linked ---------------------
			{
				for (int j = 0; j < countryVector.at(i)->getNumberAdjacency(); j++) // cycle through the country adjacent countries
				{
					if (countryVector.at(i)->getAdjacencyAt(j)->isLinked()) //if one of them is linked
					{
						countryVector.at(i)->setLinked(true); // set the country to linked
						linkedCounter++;					// add to the counter

						if (linkedCounter == numbrCountry)	// if number of linked countries is equal to the total number of countries return true
						{
							cout << "all countries are linked" << endl;
							return true;
						}

						i--;	// remove one i so that the newly linked country goes through the first "isLinked" condition and cycle through its adjacent countries and link them if they need to be linked
						break;
					}
				}
			}
		}
	}

	if (linkedCounter < numbrCountry)
	{
		cout << "Not all countries are linked" << endl;
		return false;
	}

}


bool MapChecker::areContinentLinked(int a) //check if all countries belonging to a continent are linked between themselves
{
		continentVector.at(a)->getCountryMembersAt(0)->setLinked(true); // set first data as "linked"
		int linkedCounter = 1; // set a counter that add to himself everytime a country is linked to the "linked continent graph"
		int initCounter = 0;
		while ( initCounter < linkedCounter) //While linked counter grows, cycle through the array
		{
			initCounter = linkedCounter; //update initCounter
			for (int i = 0; i < continentVector.at(a)->getNumberMembers(); i++) // Cycle through all the country nodes within the continent
			{
				if ((continentVector.at(a)->getCountryMembersAt(i)->isLinked() == true) && (continentVector.at(a)->getCountryMembersAt(i)->getContinent() == continentVector.at(a))) // if country is linked && if linked country belong to continent-----------------------------
				{
					for (int j = 0; j < continentVector.at(a)->getCountryMembersAt(i)->getNumberAdjacency(); j++) // for all the adjacent country to the previous country
					{
						if ((continentVector.at(a)->getCountryMembersAt(i)->getAdjacencyAt(j)->isLinked() == false) && (continentVector.at(a)->getCountryMembersAt(i)->getAdjacencyAt(j)->getContinent() == continentVector.at(a))) // if they are not linked && belong to the continent
						{
							continentVector.at(a)->getCountryMembersAt(i)->getAdjacencyAt(j)->setLinked(true); // link them
							linkedCounter++;										// add to the counter

							if (linkedCounter == continentVector.at(a)->getNumberMembers()) //if counter is equal to the number of country exit function
							{
								cout << "all countries belonging to the continent " + continentVector.at(a)->getContName() + " are linked" << endl;
								return true;
							}
						}
					}
				}

				else if ((continentVector.at(a)->getCountryMembersAt(i)->isLinked() == false) && continentVector.at(a)->getCountryMembersAt(i)->getContinent() == continentVector.at(a)) // if country is not linked && if linked country belong to continent ---------------------
				{
					for (int j = 0; j < continentVector.at(a)->getCountryMembersAt(i)->getNumberAdjacency(); j++) // cycle through the country adjacent countries
					{
						if ((continentVector.at(a)->getCountryMembersAt(i)->getAdjacencyAt(j)->isLinked() == true) && (continentVector.at(a)->getCountryMembersAt(i)->getAdjacencyAt(j)->getContinent() == continentVector.at(a))) //if one of them is linked
						{
							continentVector.at(a)->getCountryMembersAt(i)->setLinked(true); // set the country to linked
							linkedCounter++;					// add to the counter

							if (linkedCounter == continentVector.at(a)->getNumberMembers())	// if number of linked countries is equal to the total number of countries return true
							{
								cout << "all countries belonging to the continent  are linked" << endl;
								return true;
							}

							i--;	// remove one i so that the newly linked country goes through the first "isLinked" condition and cycle through its adjacent countries and link them if they need to be linked
							break;
						}
					}
				}
			}
		}
		if (linkedCounter < continentVector.at(a)->getNumberMembers())
		{
			cout << "Not all countries in continent " + continentVector.at(a)->getContName() + " are linked" << endl;
			return false;
		}
}


bool MapChecker::haveDuplicateCountry() //Check countryVector for duplicate name
{
	for (int i = 0; i < numbrCountry; i++) // cycle through the countryVector
	{
		for (int j = 0; j < numbrCountry; j++) // cycle through the countryVector
		{

			if (!countryVector.at(i)->getName().compare(countryVector.at(j)->getName()) && i != j) // compares names, if they are equivalent and not originating from the same country, return an error message and false
			{
				cout << "Invalid map, duplicate item name " + countryVector.at(i)->getName() << endl;

				return false;
			}
		}
	}
	cout << "No duplicate country name found" << endl;
		return true;
}

bool MapChecker::haveDuplicateContinent() // Check continentVector for duplicate name
{
	for (int i = 0; i < numbrContinent; i++) // cycle through the continentVector
	{
		for (int j = 0; j < numbrContinent; j++) // cycle through the continentVector
		{

			if (!continentVector.at(i)->getContName().compare(continentVector.at(j)->getContName()) && i != j) // compares names, if they are equivalent and not originating from the same country, return an error message and false
			{
				cout << "Invalid map, duplicate item name " + continentVector.at(i)->getContName() << endl;

				return false;
			}
		}
	}
	cout << "No duplicate continent name found" << endl;
	return true;
}

bool MapChecker::haveDualBelonging()
{
	for (int i = 0; i < numbrCountry; i++) //cycle through all countries
	{
		int occurenceCount = 0; // count number of appearance of the country in continent member list and reset it when it switch countries

		for (int j = 0; j < numbrContinent; j++) //cycle through all continents
		{
			for (int k = 0; k < continentVector.at(j)->getNumberMembers(); k++) //cycle through eatch continents list
			{
				if (countryVector.at(i) == continentVector.at(j)->getCountryMembersAt(k)) // if continent is part of the list add to the occurence counter
				{
					occurenceCount++; 
					if (occurenceCount == 2) // if it occur twice, meaning that the country "belong to two continent" return an error message and false
					{
						cout << "Country: " + countryVector.at(i)->getName() + " appears in two (or more) continent list"<< endl;
						return false;
					}
				}
			}
		}
	}

	cout << "no countries are part of two continent" << endl; //if there are no countries with dual continent membership, return true
	return true;

}


bool MapChecker::isMapCoherent( int numbrPlayer) // bundles up all fonction and
{
	if (numbrCountry < numbrPlayer || numbrCountry == 0 || numbrContinent == 0) //make sure there are continents, countries and that there are more countries than players
		return false;

	if (isMapTwoWay() == false) //make sure the graph is reflexive
		return false;

	for (int i = 0; i < numbrCountry; i++) //making sure all countries have at least 1 adjacent country
	{
		if (countryVector.at(i)->getNumberAdjacency() == 0) 
			return false;
	}

	for (int i = 0; i < numbrContinent; i++) //making sure all continents have at least 1 member country
	{
		if (continentVector.at(i)->getNumberMembers() == 0)
		{
			cout << continentVector.at(i)->getContName() +" is an empty continent, map invalid" << endl;
			return false;
		}
	}

	//making sure there are no duplicate names of continents and countries
	if (this->haveDuplicateContinent() == false) 
		return false;

	if (this->haveDuplicateCountry() == false)
		return false;

	//making sure no countries belong to two continent
	if (haveDualBelonging() == false)
		return false;


	//making sure the countries inside a continents are linked a connected graph
	for (int i = 0; i < numbrContinent; i++)
	{
		if (areContinentLinked(i) == false)
			return false;
	}

	//reseting the linked value to false
	for (int i = 0; i < numbrCountry; i++)
	{
		countryVector.at(i)->setLinked(false);
	}
	
	//checking if the whole map is a linked graph
	if(isMapLinked() == false)
		return false;
	


	return true;
}