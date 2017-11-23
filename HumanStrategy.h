#pragma once

#include "Strategy.h"
#include "Country.h"
#include "Continent.h"

class Player;
#include "Player.h"

class HumanStrategy : public Strategy
{
private:
	Player* aPlayer;

public:
	void reinforceStrat();
	void attackStrat();
	void fortificationStrat();

	HumanStrategy(Player*);
	~HumanStrategy();
};