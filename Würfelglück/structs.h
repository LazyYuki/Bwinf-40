#include "include.h"

struct Wuerfel
{
	int Seiten{};
	std::vector<int>Zahlen{};

	int wuerfeln()
	{
		int random = rand() % (this->Zahlen.size()-1);
		return Zahlen[random];
	}
};

struct Spieler
{

};