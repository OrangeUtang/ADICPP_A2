#include "DeckOfCards.h"
#include "Cards.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <stack>
#include "Hand.h"
#include <string>

using namespace std;

int NumOfCards;
stack<Cards*> Deck;

DeckOfCards::DeckOfCards()
{

}

DeckOfCards::DeckOfCards(vector<string*> countriesName, int numOfCountries)
{
	NumOfCards = numOfCountries;

	string tempType;
	srand(time(0));
	int zero = 0, one = 0, two = 0;

	for(int i = 0; i < NumOfCards; i++)
	{
		int ran;
		while(true)
		{
			ran = rand() % 3;
			if(zero <= one && zero <= two && ran == 0)
				break;
			if(one <= zero && one <= two && ran == 1)
				break;
			if(two <= zero && two <= one && ran == 2)
				break;
		}
		switch(ran)
		{
			case 0 : tempType = "Infantry";
					zero++;
				break;
			case 1 : tempType = "Artillery";
					one++;
				break;
			case 2 : tempType = "Cavalery";
					two++;
				break;
		}
		Cards *temp = new Cards(*countriesName[i], tempType);
		Deck.push(temp);
	}
	cout << "Deck generated with size: " << Deck.size() << endl;

}

Cards DeckOfCards::Draw()
{
	if(Deck.size() == 0)
	{
		cout << "The Deck is empty." << endl;
		return Cards();
	}
	cout << "Drawing a Card ------------------------" << endl;
	Cards *temp = Deck.top();
	Deck.pop();
	cout << "Deck size is now: " << Deck.size() << endl;
	Cards c = *temp;
	return c;
}

int DeckOfCards::getNumCardsDeck()
{
	return NumOfCards;
}

bool DeckOfCards::IsEmpty()
{
	if(Deck.size() > 0)
		return false;
	return true;
}



