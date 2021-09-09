#include "Spiel.h"

Spiel::Spiel(Spieler* player1, Spieler* player2)
{
	this->player1 = player1;
	this->player2 = player2;
	this->playerArray[0] = player1;
	this->playerArray[1] = player2;
}

void Spiel::start(int loops)
{
	bool starter = true;
	bool curplayer = true;
	reset();
	for (int i = 0; i < loops; i++)
	{
		curplayer = starter;
		while (!update(curplayer))
		{
			//maybe some cout stuff
			curplayer = !curplayer; //const change between players moving
		}

		reset();
		starter = !starter;
	}
}

void Spiel::reset()
{
	//reseting figuren
	int team = 0;
	int index = 0;
	for (int i = 0; i < 8; i++)
	{
		if (i > 4) team = 1;
		if (index == 5) index = 0;
		this->playerArray[team]->figuren[index].reset(team, i);
		this->playerArray[team]->figuren[index].id = i;

		this->playerArray[team]->SpawnField.push_back(&this->playerArray[team]->figuren[index]);
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
	int index = starter;
	int wuerfelnum;

	do
	{
		wuerfelnum = playerArray[index]->wuerfel.wuerfeln();

		if (wuerfelnum == 6 && playerArray[index]->SpawnField.size() != 0)
		{
			//figur ins spiel setzen
			
		}
		else if(playerArray[index]->SpawnField.size() != 4) //min. 1 spieler auf Feld
		{
			//move figur.getpos1() by wuerfelnum
		}
		//else wird geskipped, da es keine figuren auf dem Feld gibt

	} while (wuerfelnum == 6);
	
}

void Spiel::SetFigureToSpawnField(Figur* figur)
{
	std::vector<Figur*> &figs = this->spielfeld[figur->pos].Figuren;
	for (int i = 0; i < figs.size(); i++) //find figure in spielfeld and erase it
	{
		if (figs[i] == figur)
		{
			figs.erase(figs.begin() + i);
		}
	}

	figur->pos = -1;
	figur->teampos = 5;
	figur->spieler->FigursActive -= 1;
	figur->spieler->SpawnField.push_back(figur); // add it back to spawn field
}

void Spiel::SetFigureToField(Figur* figur)
{
	figur->teampos = figur->spieler->GiveTeamPos();
	figur->pos = figur->teampos;
	this->spielfeld[figur->Startpoint].Figuren.push_back(figur);
	
	std::vector<Figur*>& figs = figur->spieler->SpawnField;
	for (int i = 0; i < figs.size(); i++) //find figure in spawnfield and erase it
	{
		if (figs[i] == figur)
		{
			figs.erase(figs.begin() + i);
		}
	}

}

