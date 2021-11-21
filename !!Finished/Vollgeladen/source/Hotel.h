#pragma once
#include "include.h"

class Hotel
{
public:
	Hotel(int EntfernungVonStart, double Bewertung, int Nummer);

	int Entfernung{};
	double Bewertung{};
	int Nummer{};
};

