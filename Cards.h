#pragma once
#include <iostream>
#include <string>

using namespace std;

class Cards
{
public:
	Cards(void);
	~Cards(void);
	Cards(string Country, string Type);
	void Print();
	string country;
	string type;
	string getCountry();
	string getType();
private:

};

