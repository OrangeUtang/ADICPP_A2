#include "HumanStrategy.h"
#include "Country.h"
#include "Player.h"
#include "Strategy.h"
#include <vector>
#include <stack>

HumanStrategy::HumanStrategy(Player* p)
{
	aPlayer = p;
}

HumanStrategy::~HumanStrategy()
{

}

void HumanStrategy::reinforceStrat()
{
	//Calculate how many reinfrocements the player can get
	aPlayer->ReinforcementsCalculation();

	Country* selectedCountry;
	int selectedCountryIndex;
	int reinforcements = aPlayer->getAvailableReinforcements();


	while (reinforcements != 0)
	{
		aPlayer->printCountries();
		
		cout << "\nWhich country would you like to reinforce? (Enter number)" << endl;
		cin >> selectedCountryIndex;


		bool isValid = false;
		//Input check on the choice of country to reinforce.
		do
		{
			if (selectedCountryIndex < 0 || selectedCountryIndex >= aPlayer->GetNumOfCountry())
			{
				selectedCountry = aPlayer->GetCountryInPosition(selectedCountryIndex);
				cout << "Invalid choice of country, please enter a correct number.";
				cin >> selectedCountryIndex;
			}

			else
			{
				selectedCountry = aPlayer->GetCountryInPosition(selectedCountryIndex);
				isValid = true;
			}

		} while (!isValid);

		cout << "You currently have " << reinforcements << " reinforcements, how many do you wish to send to " << selectedCountry->getName() << "?" << endl;
		int reinforcementsSent = 0;
		cin >> reinforcementsSent;

		isValid = false;

		//Input check on the number of reinforcements.
		while (!isValid)
		{
			if (reinforcementsSent < 0 || reinforcementsSent > reinforcements)
			{
				cout << "Invalid number of reinforcements to deploy. Please enter a correct number." << endl;
				cin >> reinforcementsSent;
			}

			else
			{
				//If the input is valid, the reinforcement is done right away.
				aPlayer->reinforce(selectedCountry, reinforcementsSent);
				reinforcements -= reinforcementsSent;

				cout << selectedCountry->getName() << " was reinforced with " << reinforcementsSent << " soldiers!" << endl;
				isValid = true;
			}
		}
	}
}

void HumanStrategy::attackStrat()
{
	string answer;
	vector<Country*> attackableCountries;
	vector<int> attackingCountryIndexes;
	attackableCountries.resize(50); //I don't know the size in advance, therefore I just use one that will be big enough.
	attackingCountryIndexes.resize(50);
	bool isDone = false;



	while (!isDone)
	{
		cout << "Do you wish to attack? (y/n)" << endl;
		cin >> answer;


		if (answer == "y" || answer == "Y")
		{
			cout << "Where do you wish to attack? (Enter number)" << endl;
			int optionNumber = 0;
			for (int i = 0; i < aPlayer->GetNumOfCountry(); ++i)
			{

				if (aPlayer->GetCountryInPosition(i)->getArmy() >= 2) //If the country has at least two armies.
				{
					cout << "Attacking from " << aPlayer->GetCountryInPosition(i)->getName() << "(" << aPlayer->GetCountryInPosition(i)->getArmy() << " Army):" << endl;
					for (int j = 0; j < aPlayer->GetCountryInPosition(i)->getAdjacencySize(); ++j)
					{
						if (aPlayer->GetCountryInPosition(i)->getAdjacencyAt(j)->getOwner() != aPlayer->GetCountryInPosition(i)->getOwner() && //If both countries have a different owner
							aPlayer->GetCountryInPosition(i)->getAdjacencyAt(j)->getArmy() < aPlayer->GetCountryInPosition(i)->getArmy()) //If the target country has less army than the attacking country
						{
							cout << optionNumber << ": " << aPlayer->GetCountryInPosition(i)->getAdjacencyAt(j)->getName() << "   Army: " << aPlayer->GetCountryInPosition(i)->getAdjacencyAt(j)->getArmy() << endl;
							attackableCountries[optionNumber] = aPlayer->GetCountryInPosition(i)->getAdjacencyAt(j);
							attackingCountryIndexes[optionNumber] = i;
							++optionNumber;
						}
					}
				}
			}
			cin >> answer;
			int ans = std::stoi(answer);
			bool isValid = false;
			
			//Input check on the chosen option.
			do
			{
				if (ans < 0 || ans > optionNumber)
				{
					cout << "Invalid attack location, please enter a valid number." << endl;
					cin >> answer;
					ans = std::stoi(answer);
				}

				else
				{
					isValid = true;
				}
			} while (!isValid);

			int numDice = 0;
			int maxDice = aPlayer->GetCountryInPosition(attackingCountryIndexes[ans])->getArmy() - attackableCountries[ans]->getArmy(); //The difference between the army of the attacking country and the target.

			cout << "How many dice do you want to roll?" << endl;
			cin >> answer;
			numDice = std::stoi(answer);
			isValid = false;
			
			//Input check on the dice number.
			do 
			{
				if (numDice > maxDice || numDice > 3 || numDice <= 0)
				{
					cout << "Invalid number of dice, please enter a valid number." << endl;
					cin >> answer;
					numDice = std::stoi(answer);
				}

				else
				{
					isValid = true;
				}
			} while (!isValid);

			aPlayer->attackAction(aPlayer->GetCountryInPosition(attackingCountryIndexes[ans]), attackableCountries[ans], numDice);
		}

		else
		{
			isDone = true; //If the answer to "Do you wish to attack" is not yes, this will end the attack loop.
		}
	}
}

void HumanStrategy::fortificationStrat()
{
	vector <Country*> fortifiableCountries;
	vector <int> fortifyingCountryIndexes;
	fortifiableCountries.resize(50);
	fortifyingCountryIndexes.resize(50);
	string answer;
	int ans;
	int army;

	cout << "Do you wish to fortify (y/n)" << endl;
	cin >> answer;

	if (answer == "y" || answer == "Y")
	{
		int numberOption = 0;
		cout << "Where do you wish to fortify? (Enter number): " << endl;
		for (int i = 0; i < aPlayer->GetNumOfCountry(); ++i)
		{
			if (aPlayer->GetCountryInPosition(i)->getArmy() > 1)
			{
				cout << "Fortifying from " << aPlayer->GetCountryInPosition(i)->getName() << " (Army: " << aPlayer->GetCountryInPosition(i)->getArmy() << ") :" << endl;
				for (int j = 0; j < aPlayer->GetCountryInPosition(i)->getNumberAdjacency(); ++j)
				{
					if (aPlayer->GetCountryInPosition(i)->getAdjacencyAt(j)->getOwner() == aPlayer->GetCountryInPosition(i)->getOwner()) //If a country and its adjacent have the same owner.
					{
						cout << numberOption << ": " << aPlayer->GetCountryInPosition(i)->getAdjacencyAt(j)->getName() << "   Army: " << aPlayer->GetCountryInPosition(i)->getAdjacencyAt(j)->getArmy() << endl;
						fortifiableCountries[numberOption] = aPlayer->GetCountryInPosition(i)->getAdjacencyAt(j);
						fortifyingCountryIndexes[numberOption] = i;
						++numberOption;
					}
				}
			}
		}

		cin >> answer;
		ans = std::stoi(answer);
		bool isValid = false;
		
		//Input check on the choice of country to fortify.
		do 
		{
			if (ans < 0 || ans > numberOption)
			{
				cout << "Invalid fortification option, please enter a valid number: " << endl;
				cin >> answer;
				ans = std::stoi(answer);
			}
			else
			{
				isValid = true;
			}
		} while (!isValid);

		cout << "How much army do you want to transfer?" << endl;
		cin >> army;
		
		isValid = false;

		//Input check on the amount of army to transfer.
		do
		{
			if (army < 0 || army > aPlayer->GetCountryInPosition(fortifyingCountryIndexes[ans])->getArmy())
			{
				cout << "Invalid army amount, please enter a valid number: " << endl;
				cin >> army;
			}
			else
			{
				isValid = true;
			}
		} while (!isValid);

		aPlayer->fortify(aPlayer->GetCountryInPosition(fortifyingCountryIndexes[ans]), fortifiableCountries[ans], army);
	}

}