#include "Tag.h"

Tag::Tag(int NochZuFahren, int Tag, int standort, int Startpunkt, std::vector<Hotel*> Hotels)
{
	if (Tag == 0) //Init Tag
	{
		this->hotel = &PlaceHolder;
		this->NochZuFahren = NochZuFahren;
	}
	else
	{
		this->MaxFahren = 360; //6 AutoStunden in AutoMinuten
		this->MinFahren = NochZuFahren - (5 - Tag) * 360;
		this->MaxRange = standort + this->MaxFahren;
		this->MinRange = standort + this->MinFahren;
		this->hotel = this->Finden(Hotels);
		this->NochZuFahren = Startpunkt - this->hotel->Entfernung;
		this->startpunkt = Startpunkt;
	}
}

Hotel* Tag::Finden(std::vector<Hotel*> Hotels)
{
	Hotel* BestFind = &this->PlaceHolder;
	for (Hotel* h : Hotels)
	{
		if (h->Entfernung >= this->MinRange && h->Entfernung <= this->MaxRange) //if in range
		{
			if (BestFind->Bewertung <= h->Bewertung)
			{
				this->HotelsInRange.clear(); //to clean the other hotels
				BestFind = h;
			}
			this->HotelsInRange.push_back(h);
		}
	}

	return BestFind;
}

void Tag::Finden()
{
	Hotel* BestFind = &this->PlaceHolder;

	for (int i = 0; i < this->HotelsInRange.size(); i++)
	{
		if (BestFind->Bewertung <= this->HotelsInRange[i]->Bewertung)
		{
			this->HotelsInRange.erase(this->HotelsInRange.begin(), this->HotelsInRange.begin() + i);
			BestFind = this->HotelsInRange[i];
		}
	}

	this->hotel = BestFind;
	this->NochZuFahren = this->startpunkt - this->hotel->Entfernung;
}

void Tag::PrintTag()
{
	std::cout << "MaxFahren: " << this->MaxFahren << std::endl;
	std::cout << "MinFahren: " << this->MinFahren << std::endl;
	std::cout << "MaxRange: " << this->MaxRange << std::endl;
	std::cout << "MinRange: " << this->MinRange << std::endl;
	std::cout << "Hotel: " << this->hotel->Entfernung << std::endl;
	std::cout << "Noch zu Fahren: " << this->NochZuFahren << std::endl << std::endl;
}