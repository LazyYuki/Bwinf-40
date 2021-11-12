#pragma once
#include "include.h"
#include "Hotel.h"

class Tag
{
public:
	Tag(int NochZuFahren, int Tag, int standort, int Startpunkt, std::vector<Hotel*> Hotels);
	Hotel* Finden(std::vector<Hotel*> Hotels);
	void Finden();
	void PrintTag();

	int MaxFahren{};
	int MinFahren{};
	int MaxRange{};
	int MinRange{};
	Hotel* hotel{};
	int NochZuFahren{};
	std::vector<Hotel*> HotelsInRange{};

private:
	Hotel PlaceHolder{0, -1.1, -1};
	int startpunkt{};
};

