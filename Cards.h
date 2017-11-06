#pragma once
#include <iostream>
#include <string>

using namespace std;

class Cards
{
public:
	Cards(void);
	~Cards(void);
	Cards(string Country,string Type);
	void Print();
	string getCountry();
	string getType();
	string country;
	string type;
private:

};

