#pragma once
#include <iostream>
#include "Cards.h"

using namespace std;

class Hand
{
public:
	Hand(void);
	Cards hand[5];
	void AddCardToHand(Cards c);
	void PrintHand();
	int Exchange();
private:
	void DefineSoldiers();
};

