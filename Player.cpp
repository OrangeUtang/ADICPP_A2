#include "Player.h"
#include "Country.h"
#include "Hands.h"
#include <iostream>
#include <vector>
#include <string>



Player::Player(void)
{
	Hand hand;
	countries;

}

Player::~Player(void)
{

}


void Player::Reinforce()
{
	cout << "The player Reinforeces!" << endl;
}

void Player::Attack()
{
	cout << "The player Attacks!" << endl;
	d1.roll();

}

void Player::Fortify()
{
	cout << "The player Fortities!" << endl;
}

void Player::printCountries() {


	for (int i = 0; i < 5; i++)
	{
		string temp = countries.at(i)->getName();
		cout << "Countries " << i << " : " << countries.at(i)->getName() << endl;
	}

}

void Player::printHand()
{

	for (int i = 0; i < 5; i++)
	{
		hand.PrintHand();

	}

}
