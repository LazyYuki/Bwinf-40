#pragma once
#include "include.h"
#include "fileManager.h"


class Spieler;

struct Figur
{
	Spieler* spieler{};
	int Startpoint{}; //startpoint on spielfeld
	int teampos{0}; //pos in moving | 0 best - 4 worst | 5 spawnfield | 6 in Zielfeld
	int pos{}; //0 - 40 playing field | -1 - -4 zielfield
	int id{};

	void reset(int team, int pos)
	{
		if (team == 0) this->Startpoint = 0;
		else this->Startpoint = 21;
		id = pos;
	}

	void checkForInZiel(int lowestZielFeld)
	{
		lowestZielFeld *= -1;
		if (lowestZielFeld + 1 == this->pos) teampos = 6; //is in the finalzielspot
	}
};

struct Wuerfel
{
	int Seiten{};
	std::vector<int>Zahlen{};

	int wuerfeln()
	{
		int random = rand() % (this->Zahlen.size() - 1);
		return Zahlen[random];
	}
};

class Spieler
{
public:
	Spieler(std::string wuerfelS, int team);
	//Stats
	int Wins{ 0 };
	int AnzahlWuerfen{ 0 };
	
	//for game
	int FigursActive{ 0 }; //keepstrack of the figurs on field
	Wuerfel wuerfel{};
	std::vector<Figur>figuren{};
	std::vector<Figur*> SpawnField; //every figur has one slot
	std::vector<Figur*> OnAField; //A Field means Starter Field
	std::array<Figur*, 4> ZielFeldArray = {nullptr}; //0 - first Feld | 3 - Last Feld

	int GiveTeamPos();
	int lowestZielFeld();
	bool onSpawnField(int index);
};