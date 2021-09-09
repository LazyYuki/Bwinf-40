#include "include.h"

struct Member
{
	int beliebtestes{2};
	std::vector<int> Tage{};

	void BeliebtesterTag()
	{
		for (int Tag : Tage)
		{
			if (Tag < beliebtestes) beliebtestes = Tag;
			if (beliebtestes == 0) break; //beliebtestes ist max
		}
	}

	int VeränderteTage(int index) //Wie viele Tage verändert werden müssen um es beliebt zu machen
	{
		int output{0};
		int TagBeliebtheit = this->Tage[index];

		for (int i = 0; i < this->Tage.size(); i++)
		{
			if (i == index) continue;
			else if (TagBeliebtheit > this->Tage[i]) output++;

		}

		return output;
	}
};

struct Tag
{
	int index{};
	int beliebtheit{};
	int veränderteEinträge{0};
};