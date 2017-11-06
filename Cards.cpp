#include "Cards.h"
#include <iostream>
#include <string>

using namespace std;


string country;
string type;


Cards::Cards()
{
	Cards::country = "DefaultCountry";
	Cards::type = "DefaultType";
}

Cards::Cards(std:: string Country, std:: string Type)
{
	Cards::country = Country;
	Cards::type = Type;
}

Cards::~Cards()
{

}

void Cards::Print()
{
	if(!country.empty())
		cout << "The Country is: " << country << " and the type is: " << type << endl;
	else
		cout << "Empty" << endl;
}







