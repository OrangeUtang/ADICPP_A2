#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"

using namespace std;

class Hand
{
public:
	Hand();
	void AddCardToHand(Cards c);
	void PrintHand();
	int Exchange();
	Cards hand[5];

private:
	void DefineSoldiers();
};
