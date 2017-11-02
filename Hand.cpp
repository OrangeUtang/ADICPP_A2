#include "Hand.h"
#include <iostream>
#include "Cards.h"

using namespace std;

int Soldiers = 2;
Cards hand[5];

Hand::Hand()
{

}



void Hand::AddCardToHand(Cards card)
{
	for (int i = 0; i < 5; i++)
	{
		Cards c = hand[i];
		if (c.country.empty())
		{
			hand[i] = card;
			break;
		}
	}
}

void Hand::PrintHand()
{
	cout << "------------- PRINTING HAND --------------------" << endl;
	for (int i = 0; i < 5; i++)
	{
		Cards *c = &hand[i];
		if (c != NULL)
			hand[i].Print();
	}
	cout << "------------- END OF PRINT --------------------" << endl;
}

int Hand::Exchange()
{
	cout << endl << "------------ EXCHANGING CARDS ----------------" << endl;
	int inf = 0, art = 0, cav = 0;
	bool receive = false;
	for (int i = 0; i < 5; i++)
	{
		Cards *c = &hand[i];
		if (c != NULL)
		{
			if (!hand[i].type.compare("Infantry"))
				inf++;
			else
				if (!hand[i].type.compare("Artillery"))
					art++;
				else
					if (!hand[i].type.compare("Cavalery"))
						cav++;
		}
	}

	if (inf >= 3)
	{
		inf = 3;
		for (int i = 0; i < 5; i++)
		{
			Cards *c = &hand[i];
			if (c != NULL && inf > 0)
			{
				if (!hand[i].type.compare("Infantry"))
				{
					hand[i].~Cards();
					inf--;
				}
			}
		}
		DefineSoldiers();
		receive = true;
	}
	else
	{
		if (art >= 3)
		{
			art = 3;
			for (int i = 0; i < 5; i++)
			{
				Cards *c = &hand[i];
				if (c != NULL && art > 0)
				{
					if (!hand[i].type.compare("Artillery"))
					{
						hand[i].~Cards();
						art--;
					}

				}
			}
			DefineSoldiers();
			receive = true;
		}
		else
		{
			if (cav >= 3)
			{
				cav = 3;
				for (int i = 0; i < 5; i++)
				{
					Cards *c = &hand[i];
					if (c != NULL && cav > 0)
					{

						if (!hand[i].type.compare("Cavalery"))
						{
							hand[i].~Cards();
							cav--;
						}
					}
				}
				DefineSoldiers();
				receive = true;
			}
			else
				if (cav > 0 && inf > 0 && art > 0)
				{
					cav = 1;
					inf = 1;
					art = 1;
					for (int i = 0; i < 5; i++)
					{
						Cards *c = &hand[i];
						if (c != NULL)
						{
							if (!hand[i].type.compare("Cavalery") && cav > 0)
							{
								hand[i].~Cards();
								cav--;
							}
							if (!hand[i].type.compare("Infantry") && inf > 0)
							{
								hand[i].~Cards();
								inf--;
							}
							if (!hand[i].type.compare("Artillery") && art > 0)
							{
								hand[i].~Cards();
								art--;
							}
						}
					}
					DefineSoldiers();
					receive = true;
				}
		}
	}
	if (receive)
	{
		cout << "You have received: " << Soldiers << " soldiers." << endl;
		cout << "------------ END EXCHANGE ----------------" << endl << endl;
		return Soldiers;
	}
	else
	{
		cout << "The requirements for the exchange were not met" << endl;
		cout << "------------ END EXCHANGE ----------------" << endl << endl;
		return 0;
	}
}

void Hand::DefineSoldiers()
{
	if (Soldiers < 12)
		Soldiers = Soldiers + 2;
	else
		if (Soldiers = 12)
			Soldiers = 15;
		else
			Soldiers = Soldiers + 5;
}




