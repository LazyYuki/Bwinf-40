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
	for (int i = 0; i < 4; i++)
	{
		if (i == 4) team = 1;
		this->playerArray[team]->figuren[i].reset(team, i);
		this->playerArray[team]->figuren[i].id = i;

		this->playerArray[team]->SpawnField.push_back(&this->playerArray[team]->figuren[i]);
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
			SetFigureToField(playerArray[index]->SpawnField[0]);
		}
		else if(playerArray[index]->SpawnField.size() != 4) //min. 1 spieler auf Feld
		{
			if (playerArray[index]->OnAField.size() != 0)
			{
				//move figur.startpoint by wuerfelnum
			}
			else
			{
				//move figur.getpos1() by wuerfelnum
			}
		}
		//else wird geskipped, da es keine figuren auf dem Feld gibt

	} while (wuerfelnum == 6);
	
}

void Spiel::SetFigureToSpawnField(Figur* figur)
{
	for (int i = 0; i < this->spielfeld[figur->pos].Figuren.size(); i++) //find figure in spielfeld and erase it
	{
		if (this->spielfeld[figur->pos].Figuren[i] == figur)
		{
			this->spielfeld[figur->pos].Figuren.erase(this->spielfeld[figur->pos].Figuren.begin() + i);
		}
	}

	for (int i = 0; i < figur->spieler->OnAField.size(); i++) //find figure in OnAField and erase it
	{
		if (figur->spieler->OnAField[i] == figur)
		{
			figur->spieler->OnAField.erase(figur->spieler->OnAField.begin() + i);
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
	figur->pos = figur->Startpoint;
	figur->spieler->OnAField.push_back(figur); //now stands on A Field
	this->spielfeld[figur->Startpoint].Figuren.push_back(figur);//add to Spielfeld
	figur->spieler->FigursActive += 1; //is now active figur
	
	for (int i = 0; i < figur->spieler->SpawnField.size(); i++) //find figure in spawnfield and erase it
	{
		if (figur->spieler->SpawnField[i] == figur)
		{
			figur->spieler->SpawnField.erase(figur->spieler->SpawnField.begin() + i);
		}
	}
}

void Spiel::DeleteFigurFromField(Figur* figur)
{
	for (int i = 0; i < spielfeld[figur->pos].Figuren.size(); i++) //find figure in spawnfield and erase it
	{
		if (spielfeld[figur->pos].Figuren[i] == figur)
		{
			spielfeld[figur->pos].Figuren.erase(spielfeld[figur->pos].Figuren.begin() + i);
		}
	}
}

void Spiel::moveFigur(Figur* figur, int num)
{
	int PlaceToGo = figur->pos + num;

	if (figur->pos < 0) //figur is already in zielarray
	{
		PlaceToGo = figur->pos - num;
		int lowestZielFeld = figur->spieler->lowestZielFeld() * -1 - 1;
		int FeldAvaible = figur->spieler->onSpawnField(PlaceToGo);

		if (PlaceToGo > lowestZielFeld && FeldAvaible)
		{
			figur->spieler->ZielFeldArray[figur->pos + 1] = nullptr; //Setting the place where he was to nullptr
			figur->spieler->ZielFeldArray[PlaceToGo * -1 - 1] = figur; //adding to zielfeldarray
			figur->pos = PlaceToGo;
			figur->checkForInZiel(lowestZielFeld); //check if in Final Ziel spot
		}
	}

	int check = 0;
	if (figur->Startpoint == 0) check = 40; //check = field bevor start
	else check = 20;

	if (PlaceToGo > check && figur->pos <= check) //if place to go is bigger the bevor start -> has to go to ziel
	{
		int AvaibleAfter = check - figur->pos - num * -1; //how many times you can go after going on field 40
		int lowestZielFeld = figur->spieler->lowestZielFeld();
		int FeldAvaible = figur->spieler->onSpawnField(AvaibleAfter);

		if (AvaibleAfter - 1 < lowestZielFeld && FeldAvaible)
		{
			this->DeleteFigurFromField(figur); //delete from spielfeld
			figur->spieler->ZielFeldArray[AvaibleAfter - 1] = figur; //adding to zielfeldarray
			figur->pos = AvaibleAfter * -1;
			figur->checkForInZiel(lowestZielFeld); //check if in Final Ziel spot
		}
	}
	else
	{
		this->DeleteFigurFromField(figur); //delete from spielfeld
		this->spielfeld[PlaceToGo].Figuren.push_back(figur);
	}
}