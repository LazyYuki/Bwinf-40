#include "waage.h"

bool waage::Possible(std::vector<Gewicht> gewichte, int index, int balance)
{
	int lol{};
	std::cout << balance << std::endl;
	std::cin >> lol;

	for (int i = index; i < gewichte.size(); i++)
	{
		balance += gewichte[i].gewicht;
		std::cout << balance << std::endl;
		if(balance == 0 || Possible(gewichte, index + 1, balance)) return true;

		std::cout << balance << std::endl;
		balance -= (2*gewichte[i].gewicht);
		std::cout << balance << std::endl;

		if(balance == 0 || Possible(gewichte, index + 1, balance)) return true;

		balance += gewichte[i].gewicht;
		if(balance == 0 || Possible(gewichte, index + 1, balance)) return true;
	}

	return false;
}