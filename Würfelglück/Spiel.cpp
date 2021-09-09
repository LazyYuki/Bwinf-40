#include "Spiel.h"

Spiel::Spiel(Spieler* player1, Spieler* player2)
{
	this->player1 = player1;
	this->player2 = player2;
}

void Spiel::start(int loops)
{
	bool starter = true;
	for (int i = 0; i < loops; i++)
	{
		while (!update(starter))
		{
			//maybe some cout stuff
		}

		reset();
		starter = !starter;
	}
}

void Spiel::reset()
{
	//reseting figuren
	int team = 0;
	for (int i = 0; i < 8; i++)
	{
		if (i > 4) team = 1;
		this->player1->figuren[i].reset(team, i);
	}

	//reseting field
	spielfeld.clear();
	for (int i = 0; i < 40; i++)
	{
		Spielfeld temp;
		temp.pos = i;
		spielfeld.push_back(temp);
	}
}

bool Spiel::update(bool starter)
{

}