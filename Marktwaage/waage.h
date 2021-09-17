#pragma once
#include "include.h"

struct Gewicht
{
	int gewicht;
};

class waage
{
public:
	static bool Possible(std::vector<Gewicht> gewichte, int index, int balance);
};

