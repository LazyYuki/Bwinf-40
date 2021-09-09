#pragma once
#include "include.h"
#include "fileManager.h"


class Spieler;

struct Figur
{
	Spieler* spieler{};
	int Startpoint{}; //startpoint on spielfeld
	int teampos{0}; //pos in Array | 0 best - 4 worst | 5 spawnfield
	int pos{};
	int id{};

	void reset(int team, int pos)
	{
		if (team == 0) this->Startpoint = 0;
		else this->Startpoint = 21;
		teampos = pos;
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
	std::vector<Figur*>SpawnField{};
	Figur* ZielFeldArray[4];

	int GiveTeamPos();
};