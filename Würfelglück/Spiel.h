#pragma once
#include "include.h"
#include "Spieler.h"

struct Spielfeld
{
	int pos{};
	std::vector<Figur*>Figuren{};
};

class Spiel
{
public:
	std::vector<Spielfeld> spielfeld{};

	Spiel(Spieler* player1, Spieler* player2);

	void start(int loops);
	void reset();
	bool update(bool starter); //true someone won

	void SetFigureToSpawnField(Figur* figur);
	void SetFigureToField(Figur* figur);

private:
	Spieler* player1;
	Spieler* player2;
	Spieler* playerArray[2];
};

