#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "DeckOfCards.h"
#include "Hand.h"
#include "Dice.h"
#include "Dice_rolling.h"
class Country;
#include "Country.h"

class Player
{

private:
	Hand hand;
	Dice_rolling d1;
	vector <Country*> countries;

public:
	Player(void);
	~Player(void);
	void Player::Reinforce();
	void Player::Attack();
	void Player::Fortify();
	void printCountries();
	void printHand();
};
