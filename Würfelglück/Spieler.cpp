#include "Spieler.h"

Spieler::Spieler(std::string wuerfelS, int team)
{
    this->wuerfel.Zahlen = fileManager::VstringToVint(fileManager::split(wuerfelS, ' '));

    int Startpoint{};
    if (team == 0) Startpoint = 0; //startpoints on field
    else Startpoint = 21; //startpoints on field

    for (int i = 0; i < 4; i++)
    {
        Figur figur;
        figur.Startpoint = Startpoint;
        figur.teampos = i;
        figur.spieler = this;
        this->figuren.push_back(figur);
    }
}