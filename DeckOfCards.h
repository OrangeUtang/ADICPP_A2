#pragma once
#include <iostream>
#include "Cards.h"
#include "Hand.h"

using namespace std;

class DeckOfCards
{
public:
	DeckOfCards();
	DeckOfCards(vector<string*>,int);
	Cards Draw();
	int getNumCardsDeck();
	bool IsEmpty();
	
private:
	int numOfCards;
	
};

