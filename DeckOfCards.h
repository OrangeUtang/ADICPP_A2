#pragma once
#include <iostream>
#include "Cards.h"
#include "Hand.h"

using namespace std;

class DeckOfCards
{
public:
	DeckOfCards(string[], int);
	Cards Draw();
	bool IsEmpty();

private:
	int numOfCards;

};

