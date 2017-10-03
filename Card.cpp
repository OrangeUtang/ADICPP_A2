#include "Cards.h"
#include <iostream>
#include <string>

using namespace std;


string country;
string type;


Cards::Cards()
{
	//cout << "Default Contructor";
}

Cards::Cards(std::string Country, std::string Type)
{
	Cards::country = Country;
	Cards::type = Type;
}

Cards::~Cards()
{

}



void Cards::Print()
{
	if (!country.empty())
		cout << "The Country is: " << country << " and the type is: " << type << endl;
	else
		cout << "Empty" << endl;
}

string Cards::getCountry()
{
	return country;
}

string Cards::getType()
{
	return type;
}







