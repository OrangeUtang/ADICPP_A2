#include "Country.h"
#include "Continent.h"
#include "MapChecker.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	cout << "Valid map exemple" << endl;


	
	int numberContinent = 2;

	int numberCountries = 5;

	vector <Country*> countries;
	vector <Continent*> continents;

	countries.resize(numberCountries);
	continents.resize(numberContinent);


	//filling the country vector
	countries.at(0) = new Country("Portugal", 2);
	countries.at(1) = new Country("Spain", 3);
	countries.at(2) = new Country("France", 1);

	countries.at(3) = new Country("Morroco", 3);
	countries.at(4) = new Country("Algeria", 1);

	/*
	these are the implemented adjacencies
	portugal->spain, morroco
	spain->portugal, france, morroco
	france->spain
	morroco->portugal, spain, algeria
	algeria ->morroco
	
	*/

	//portugal
	countries.at(0)->setAdjacencyAt(0, countries.at(1));
	countries.at(0)->setAdjacencyAt(1, countries.at(3));
	
	//spain
	countries.at(1)->setAdjacencyAt(0, countries.at(0));
	countries.at(1)->setAdjacencyAt(1, countries.at(2));
	countries.at(1)->setAdjacencyAt(2, countries.at(3));

	//france
	countries.at(2)->setAdjacencyAt(0, countries.at(1));

	//morroco
	countries.at(3)->setAdjacencyAt(0, countries.at(0));
	countries.at(3)->setAdjacencyAt(1, countries.at(1));
	countries.at(3)->setAdjacencyAt(2, countries.at(4));

	//algeria
	countries.at(4)->setAdjacencyAt(0, countries.at(3));

	//filling the continent array
	continents.at(0) = new Continent("Europe", 3);
	continents.at(1) = new Continent("Africa", 2);

	//filling the continents country lists;

	//Europe
	continents.at(0)->setCountryMembersAt(0, countries.at(0)); // portugal
	continents.at(0)->setCountryMembersAt(1, countries.at(1)); // Spain
	continents.at(0)->setCountryMembersAt(2, countries.at(2)); // France

	//Africa
	continents.at(1)->setCountryMembersAt(0, countries.at(3)); // morroco
	continents.at(1)->setCountryMembersAt(1, countries.at(4)); // algeria

	//setting countrie's continent
	countries.at(0)->setContinent(continents.at(0)); // portugal -> europe
	countries.at(1)->setContinent(continents.at(0)); // spain -> europe
	countries.at(2)->setContinent(continents.at(0)); // france -> europe
	countries.at(3)->setContinent(continents.at(1)); // morroco -> africa
	countries.at(4)->setContinent(continents.at(1)); // algeria -> africa

	//validating map

	MapChecker mapCheck1(countries, continents);
	
	mapCheck1.isMapCoherent(2); // fictional number of player
	
	//resetting for test two-------------------------------------------------------------
	for (int i = 0; i < 5; i++)
	{
		countries.at(i)->setLinked(false);
	}


	system("pause");

	cout << "Test number two , invalid map test, unconnected continent (europe) map" << endl;

	//setting france only adjacency to algeria 
	countries.at(2)->setAdjacencyAt(0, countries.at(4));

	//setting spain dangling adjacency to algeria
	countries.at(1)->setAdjacencyAt(1, countries.at(4));
	
	//resetting new adjacency for algeria and continent
	delete countries.at(4);
	countries.at(4) = new Country("Algeria", 3);
	countries.at(4)->setAdjacencyAt(0, countries.at(1));
	countries.at(4)->setAdjacencyAt(1, countries.at(2));
	countries.at(4)->setAdjacencyAt(2, countries.at(3));
	countries.at(4)->setContinent(continents.at(1));

	mapCheck1.isMapCoherent(2);

	//resetting for test three---------------------------------------------------
	for (int i = 0; i < 5; i++)
	{
		countries.at(i)->setLinked(false);
	}

	system("pause");

	cout << "Test number three, unreflexive graph (link from portugal to france is missing)" << endl;

	//reseting spain link to france (so continent is connected) but set a link from france to portugal
	vector <Country*> franceAdj = {countries.at(0), countries.at(1), countries.at(4)};
	countries.at(2)->setAdjacency(franceAdj); //france -> portugal, spain, algeria


	//making spain adjacency coherent again
	vector <Country*> spainAdj = { countries.at(0), countries.at(2), countries.at(3), countries.at(4) }; // spain -> all the others
	countries.at(1)->setAdjacency(spainAdj);
	



	MapChecker mapCheck2(countries, continents);


	mapCheck2.isMapCoherent(2);

	//resetting for test four-----------------------------------------

	for (int i = 0; i < 5; i++)
	{
		countries.at(i)->setLinked(false);
	}

	system("pause");

	cout << "Test number Four, appearance of the same country in two different continent" << endl;

	//setting link 2 from france to algeria again
	countries.at(2)->setAdjacencyAt(0, countries.at(4));

	//change africa continent to include spain
	delete continents.at(1);
	continents.at(1) = new Continent("Africa", 3);
	continents.at(1)->setCountryMembersAt(0, countries.at(1));
	continents.at(1)->setCountryMembersAt(1, countries.at(3));
	continents.at(1)->setCountryMembersAt(2, countries.at(4));

	MapChecker mapCheck3(countries, continents);

	mapCheck3.isMapCoherent(2);

	//resetting for test five---------------------------------------------------

	for (int i = 0; i < 5; i++)
	{
		countries.at(i)->setLinked(false);
	}

	system("pause");

	cout << "Test number five, empty continent Asia " << endl;

	//deleting spain from africa and reseting the whole thign
	delete continents.at(1);
	continents.at(1) = new Continent("Africa", 2);
	continents.at(1)->setCountryMembersAt(0, countries.at(3));
	continents.at(1)->setCountryMembersAt(1, countries.at(4));

	continents.resize(3);
	continents.at(2) = new Continent("Asia", 0);

	MapChecker mapCheck4(countries, continents);

	mapCheck4.isMapCoherent(2);

	//resetting for test six-----------------------------------------------------------------

	for (int i = 0; i < 5; i++)
	{
		countries.at(i)->setLinked(false);
	}

	system("pause");

	cout << "Test number six, unconnected map " << endl;

	//removing contient asia from vector
	delete continents.at(2);
	continents.resize(2);
	
	//replacing adjacency values for morroco and algeria
	vector <Country*> morroco = { countries.at(3) };
	vector <Country*> algeria = { countries.at(4) };

	countries.at(3)->setAdjacency(algeria);
	countries.at(4)->setAdjacency(morroco);

	//replacing adjacency values for europe
	vector <Country*> spain = { countries.at(1) };
	vector <Country*> ROE = { countries.at(0), countries.at(2) };

	countries.at(0)->setAdjacency(spain);
	countries.at(1)->setAdjacency(ROE);
	countries.at(2)->setAdjacency(spain);

	MapChecker mapCheck5(countries, continents);

	mapCheck5.isMapCoherent(2);

	system("pause");

	cout << " one more example of a valid map" << endl;

	vector <Country*> countries2(10);
	vector <Continent*> continents2(3);

	//creating
	countries2.at(0) = new Country("one", 1);
	countries2.at(1) = new Country("two", 2);
	countries2.at(2) = new Country("three", 2);
	countries2.at(3) = new Country("four", 2);
	countries2.at(4) = new Country("Five", 2);
	countries2.at(5) = new Country("Six", 2);
	countries2.at(6) = new Country("Seven", 2);
	countries2.at(7) = new Country("eight", 2);
	countries2.at(8) = new Country("nine", 2);
	countries2.at(9) = new Country("ten", 1);
	
	continents2.at(0) = new Continent("onetwothree", 3);
	continents2.at(1) = new Continent("fourfivesixseven", 4);
	continents2.at(2) = new Continent("eightnineten", 3);

	//setting adjacency
	countries2.at(0)->setAdjacencyAt(0, countries2.at(1));
	countries2.at(1)->setAdjacencyAt(0, countries2.at(0));
	countries2.at(1)->setAdjacencyAt(1, countries2.at(2));
	countries2.at(2)->setAdjacencyAt(0, countries2.at(1));
	countries2.at(2)->setAdjacencyAt(1, countries2.at(3));
	countries2.at(3)->setAdjacencyAt(0, countries2.at(2));
	countries2.at(3)->setAdjacencyAt(1, countries2.at(4));
	countries2.at(4)->setAdjacencyAt(0, countries2.at(3));
	countries2.at(4)->setAdjacencyAt(1, countries2.at(5));
	countries2.at(5)->setAdjacencyAt(0, countries2.at(4));
	countries2.at(5)->setAdjacencyAt(1, countries2.at(6));
	countries2.at(6)->setAdjacencyAt(0, countries2.at(5));
	countries2.at(6)->setAdjacencyAt(1, countries2.at(7));
	countries2.at(7)->setAdjacencyAt(0, countries2.at(6));
	countries2.at(7)->setAdjacencyAt(1, countries2.at(8));
	countries2.at(8)->setAdjacencyAt(0, countries2.at(7));
	countries2.at(8)->setAdjacencyAt(1, countries2.at(9));
	countries2.at(9)->setAdjacencyAt(0, countries2.at(8));
	
	//continents 
	countries2.at(0)->setContinent(continents2.at(0));
	countries2.at(1)->setContinent(continents2.at(0));
	countries2.at(2)->setContinent(continents2.at(0));
	countries2.at(3)->setContinent(continents2.at(1));
	countries2.at(4)->setContinent(continents2.at(1));
	countries2.at(5)->setContinent(continents2.at(1));
	countries2.at(6)->setContinent(continents2.at(1));
	countries2.at(7)->setContinent(continents2.at(2));
	countries2.at(8)->setContinent(continents2.at(2));
	countries2.at(9)->setContinent(continents2.at(2));

	//setting continent list
	continents2.at(0)->setCountryMembersAt(0, countries2.at(0));
	continents2.at(0)->setCountryMembersAt(1, countries2.at(1));
	continents2.at(0)->setCountryMembersAt(2, countries2.at(2));
	continents2.at(1)->setCountryMembersAt(0, countries2.at(3));
	continents2.at(1)->setCountryMembersAt(1, countries2.at(4));
	continents2.at(1)->setCountryMembersAt(2, countries2.at(5));
	continents2.at(1)->setCountryMembersAt(3, countries2.at(6));
	continents2.at(2)->setCountryMembersAt(0, countries2.at(7));
	continents2.at(2)->setCountryMembersAt(1, countries2.at(8));
	continents2.at(2)->setCountryMembersAt(2, countries2.at(9));

	MapChecker mapcheck6(countries2, continents2);

	mapcheck6.isMapCoherent(3); 

	system("pause");

	return 0;
}