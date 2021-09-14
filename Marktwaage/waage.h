#pragma 
#include "include.h"

struct gewichtstuck
{
	int gewicht;
	int anzahl;
};

class waage
{
public:
	std::vector<gewichtstuck> gewichte{};

	bool Possible(int Gewicht);

};

